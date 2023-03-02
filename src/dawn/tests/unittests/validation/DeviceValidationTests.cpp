// Copyright 2021 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <utility>

#include "dawn/native/Device.h"
#include "dawn/native/dawn_platform.h"
#include "dawn/tests/unittests/validation/ValidationTest.h"

using ::testing::HasSubstr;

class RequestDeviceValidationTest : public ValidationTest {
  protected:
    void SetUp() override {
        ValidationTest::SetUp();
        DAWN_SKIP_TEST_IF(UsesWire());
    }

    static void ExpectRequestDeviceSuccess(WGPURequestDeviceStatus status,
                                           WGPUDevice cDevice,
                                           const char* message,
                                           void* userdata) {
        wgpu::Device device = wgpu::Device::Acquire(cDevice);
        EXPECT_EQ(status, WGPURequestDeviceStatus_Success);
        EXPECT_NE(device, nullptr);
        EXPECT_STREQ(message, nullptr);
        if (userdata != nullptr) {
            CallCheckDevice(static_cast<std::function<void(wgpu::Device)>*>(userdata),
                            std::move(device));
        }
    }

    static void ExpectRequestDeviceError(WGPURequestDeviceStatus status,
                                         WGPUDevice cDevice,
                                         const char* message,
                                         void* userdata) {
        wgpu::Device device = wgpu::Device::Acquire(cDevice);
        EXPECT_EQ(status, WGPURequestDeviceStatus_Error);
        EXPECT_EQ(device, nullptr);
        EXPECT_STRNE(message, nullptr);
    }

    template <typename F>
    static void* CheckDevice(F&& f) {
        return new std::function<void(wgpu::Device)>(f);
    }

    static void CallCheckDevice(std::function<void(wgpu::Device)>* f, wgpu::Device d) {
        (*f)(std::move(d));
        delete f;
    }
};

// Test that requesting a device without specifying limits is valid.
TEST_F(RequestDeviceValidationTest, NoRequiredLimits) {
    wgpu::DeviceDescriptor descriptor;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceSuccess,
                                      CheckDevice([](wgpu::Device device) {
                                          // Check one of the default limits.
                                          wgpu::SupportedLimits limits;
                                          device.GetLimits(&limits);
                                          EXPECT_EQ(limits.limits.maxBindGroups, 4u);
                                      }));
}

// Test that requesting a device with the default limits is valid.
TEST_F(RequestDeviceValidationTest, DefaultLimits) {
    wgpu::RequiredLimits limits = {};
    wgpu::DeviceDescriptor descriptor;
    descriptor.requiredLimits = &limits;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceSuccess,
                                      CheckDevice([](wgpu::Device device) {
                                          // Check one of the default limits.
                                          wgpu::SupportedLimits limits;
                                          device.GetLimits(&limits);
                                          EXPECT_EQ(limits.limits.maxTextureArrayLayers, 256u);
                                      }));
}

// Test that requesting a device where a required limit is above the maximum value.
TEST_F(RequestDeviceValidationTest, HigherIsBetter) {
    wgpu::RequiredLimits limits = {};
    wgpu::DeviceDescriptor descriptor;
    descriptor.requiredLimits = &limits;

    wgpu::SupportedLimits supportedLimits;
    EXPECT_TRUE(adapter.GetLimits(&supportedLimits));

    // If we can support better than the default, test below the max.
    if (supportedLimits.limits.maxBindGroups > 4u) {
        limits.limits.maxBindGroups = supportedLimits.limits.maxBindGroups - 1;
        GetBackendAdapter().RequestDevice(
            &descriptor, ExpectRequestDeviceSuccess, CheckDevice([&](wgpu::Device device) {
                wgpu::SupportedLimits limits;
                device.GetLimits(&limits);

                // Check we got exactly the request.
                EXPECT_EQ(limits.limits.maxBindGroups, supportedLimits.limits.maxBindGroups - 1);
                // Check another default limit.
                EXPECT_EQ(limits.limits.maxTextureArrayLayers, 256u);
            }));
    }

    // Test the max.
    limits.limits.maxBindGroups = supportedLimits.limits.maxBindGroups;
    GetBackendAdapter().RequestDevice(
        &descriptor, ExpectRequestDeviceSuccess, CheckDevice([&](wgpu::Device device) {
            wgpu::SupportedLimits limits;
            device.GetLimits(&limits);

            // Check we got exactly the request.
            EXPECT_EQ(limits.limits.maxBindGroups, supportedLimits.limits.maxBindGroups);
            // Check another default limit.
            EXPECT_EQ(limits.limits.maxTextureArrayLayers, 256u);
        }));

    // Test above the max.
    limits.limits.maxBindGroups = supportedLimits.limits.maxBindGroups + 1;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceError, nullptr);

    // Test worse than the default
    limits.limits.maxBindGroups = 3u;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceSuccess,
                                      CheckDevice([&](wgpu::Device device) {
                                          wgpu::SupportedLimits limits;
                                          device.GetLimits(&limits);

                                          // Check we got the default.
                                          EXPECT_EQ(limits.limits.maxBindGroups, 4u);
                                      }));
}

// Test that requesting a device where a required limit is below the minimum value.
TEST_F(RequestDeviceValidationTest, LowerIsBetter) {
    wgpu::RequiredLimits limits = {};
    wgpu::DeviceDescriptor descriptor;
    descriptor.requiredLimits = &limits;

    wgpu::SupportedLimits supportedLimits;
    EXPECT_TRUE(adapter.GetLimits(&supportedLimits));

    // Test below the min.
    limits.limits.minUniformBufferOffsetAlignment =
        supportedLimits.limits.minUniformBufferOffsetAlignment / 2;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceError, nullptr);

    // Test the min.
    limits.limits.minUniformBufferOffsetAlignment =
        supportedLimits.limits.minUniformBufferOffsetAlignment;
    GetBackendAdapter().RequestDevice(
        &descriptor, ExpectRequestDeviceSuccess, CheckDevice([&](wgpu::Device device) {
            wgpu::SupportedLimits limits;
            device.GetLimits(&limits);

            // Check we got exactly the request.
            EXPECT_EQ(limits.limits.minUniformBufferOffsetAlignment,
                      supportedLimits.limits.minUniformBufferOffsetAlignment);
            // Check another default limit.
            EXPECT_EQ(limits.limits.maxTextureArrayLayers, 256u);
        }));

    // IF we can support better than the default, test above the min.
    if (supportedLimits.limits.minUniformBufferOffsetAlignment > 256u) {
        limits.limits.minUniformBufferOffsetAlignment =
            supportedLimits.limits.minUniformBufferOffsetAlignment * 2;
        GetBackendAdapter().RequestDevice(
            &descriptor, ExpectRequestDeviceSuccess, CheckDevice([&](wgpu::Device device) {
                wgpu::SupportedLimits limits;
                device.GetLimits(&limits);

                // Check we got exactly the request.
                EXPECT_EQ(limits.limits.minUniformBufferOffsetAlignment,
                          supportedLimits.limits.minUniformBufferOffsetAlignment * 2);
                // Check another default limit.
                EXPECT_EQ(limits.limits.maxTextureArrayLayers, 256u);
            }));
    }

    // Test worse than the default
    limits.limits.minUniformBufferOffsetAlignment = 2u * 256u;
    GetBackendAdapter().RequestDevice(
        &descriptor, ExpectRequestDeviceSuccess, CheckDevice([&](wgpu::Device device) {
            wgpu::SupportedLimits limits;
            device.GetLimits(&limits);

            // Check we got the default.
            EXPECT_EQ(limits.limits.minUniformBufferOffsetAlignment, 256u);
        }));
}

// Test that it is an error to request limits with an invalid chained struct
TEST_F(RequestDeviceValidationTest, InvalidChainedStruct) {
    wgpu::PrimitiveDepthClipControl depthClipControl = {};
    wgpu::RequiredLimits limits = {};
    limits.nextInChain = &depthClipControl;

    wgpu::DeviceDescriptor descriptor;
    descriptor.requiredLimits = &limits;
    GetBackendAdapter().RequestDevice(&descriptor, ExpectRequestDeviceError, nullptr);
}

class DeviceTickValidationTest : public ValidationTest {};

// Device destroy before API-level Tick should always result in no-op and false.
TEST_F(DeviceTickValidationTest, DestroyDeviceBeforeAPITick) {
    ExpectDeviceDestruction();
    device.Destroy();
    device.Tick();
}

// Device destroy before an internal Tick should return an error.
TEST_F(DeviceTickValidationTest, DestroyDeviceBeforeInternalTick) {
    DAWN_SKIP_TEST_IF(UsesWire());

    ExpectDeviceDestruction();
    device.Destroy();
    dawn::native::DeviceBase* nativeDevice = dawn::native::FromAPI(device.Get());
    ASSERT_DEVICE_ERROR(EXPECT_TRUE(nativeDevice->ConsumedError(nativeDevice->Tick())),
                        HasSubstr("[Device] is lost."));
}
