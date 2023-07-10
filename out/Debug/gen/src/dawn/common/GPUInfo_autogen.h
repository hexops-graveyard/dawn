// Copyright 2022 The Dawn Authors
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

#ifndef SRC_DAWN_COMMON_GPUINFO_AUTOGEN_H_
#define SRC_DAWN_COMMON_GPUINFO_AUTOGEN_H_

#include <cstdint>
#include <string>

using PCIVendorID = uint32_t;
using PCIDeviceID = uint32_t;

namespace dawn::gpu_info {

// Vendor IDs
static constexpr PCIVendorID kVendorID_AMD = 0x1002;
static constexpr PCIVendorID kVendorID_Apple = 0x106b;
static constexpr PCIVendorID kVendorID_ARM = 0x13B5;
static constexpr PCIVendorID kVendorID_Google = 0x1AE0;
static constexpr PCIVendorID kVendorID_ImgTec = 0x1010;
static constexpr PCIVendorID kVendorID_Intel = 0x8086;
static constexpr PCIVendorID kVendorID_Mesa = 0x10005;
static constexpr PCIVendorID kVendorID_Microsoft = 0x1414;
static constexpr PCIVendorID kVendorID_Nvidia = 0x10DE;
static constexpr PCIVendorID kVendorID_Qualcomm = 0x5143;
static constexpr PCIVendorID kVendorID_Samsung = 0x144d;

// Vendor checks
bool IsAMD(PCIVendorID vendorId);
bool IsApple(PCIVendorID vendorId);
bool IsARM(PCIVendorID vendorId);
bool IsGoogle(PCIVendorID vendorId);
bool IsImgTec(PCIVendorID vendorId);
bool IsIntel(PCIVendorID vendorId);
bool IsMesa(PCIVendorID vendorId);
bool IsMicrosoft(PCIVendorID vendorId);
bool IsNvidia(PCIVendorID vendorId);
bool IsQualcomm(PCIVendorID vendorId);
bool IsSamsung(PCIVendorID vendorId);

// Architecture checks

// AMD architectures
bool IsAMDGCN2(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDGCN5(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDRDNA2(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDGCN1(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDGCN3(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDGCN4(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsAMDRDNA1(PCIVendorID vendorId, PCIDeviceID deviceId);

// ARM architectures
bool IsARMMidgard(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsARMBifrost(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsARMValhall(PCIVendorID vendorId, PCIDeviceID deviceId);

// Google architectures
bool IsGoogleSwiftshader(PCIVendorID vendorId, PCIDeviceID deviceId);

// Intel architectures
bool IsIntelGen7(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsIntelGen8(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsIntelGen9(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsIntelGen11(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsIntelGen12LP(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsIntelGen12HP(PCIVendorID vendorId, PCIDeviceID deviceId);

// Microsoft architectures
bool IsMicrosoftWARP(PCIVendorID vendorId, PCIDeviceID deviceId);

// Nvidia architectures
bool IsNvidiaFermi(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsNvidiaKepler(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsNvidiaMaxwell(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsNvidiaPascal(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsNvidiaTuring(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsNvidiaAmpere(PCIVendorID vendorId, PCIDeviceID deviceId);

// Qualcomm architectures
bool IsQualcommAdreno4xx(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsQualcommAdreno5xx(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsQualcommAdreno6xx(PCIVendorID vendorId, PCIDeviceID deviceId);
bool IsQualcommAdreno7xx(PCIVendorID vendorId, PCIDeviceID deviceId);

// Samsung architectures
bool IsSamsungRDNA2(PCIVendorID vendorId, PCIDeviceID deviceId);

// GPUAdapterInfo fields
std::string GetVendorName(PCIVendorID vendorId);
std::string GetArchitectureName(PCIVendorID vendorId, PCIDeviceID deviceId);

} // namespace dawn::gpu_info
#endif  // SRC_DAWN_COMMON_GPUINFO_AUTOGEN_H_
