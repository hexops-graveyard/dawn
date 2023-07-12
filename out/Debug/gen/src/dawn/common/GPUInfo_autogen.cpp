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

#include <algorithm>
#include <array>
#include <sstream>
#include <iomanip>

#include "dawn/common/GPUInfo_autogen.h"

#include "dawn/common/Assert.h"

namespace dawn::gpu_info {

namespace {

enum class Architecture {
    Unknown,
    AMD_GCN2,
    AMD_GCN5,
    AMD_RDNA2,
    AMD_GCN1,
    AMD_GCN3,
    AMD_GCN4,
    AMD_RDNA1,
    ARM_Midgard,
    ARM_Bifrost,
    ARM_Valhall,
    Google_Swiftshader,
    Intel_Gen7,
    Intel_Gen8,
    Intel_Gen9,
    Intel_Gen11,
    Intel_Gen12LP,
    Intel_Gen12HP,
    Microsoft_WARP,
    Nvidia_Fermi,
    Nvidia_Kepler,
    Nvidia_Maxwell,
    Nvidia_Pascal,
    Nvidia_Turing,
    Nvidia_Ampere,
    Qualcomm_Adreno4xx,
    Qualcomm_Adreno5xx,
    Qualcomm_Adreno6xx,
    Qualcomm_Adreno7xx,
    Samsung_RDNA2,
};

Architecture GetArchitecture(PCIVendorID vendorId, PCIDeviceID deviceId) {
    switch(vendorId) {
        case kVendorID_AMD: {
            switch (deviceId & 0xFF00) {
                case 0x1300:
                    return Architecture::AMD_GCN2;
                case 0x1500:
                case 0x1600:
                    return Architecture::AMD_GCN5;
                case 0x7400:
                    return Architecture::AMD_RDNA2;
            }
            switch (deviceId & 0xFFF0) {
                case 0x6600:
                case 0x6610:
                case 0x6660:
                case 0x6790:
                case 0x6800:
                case 0x6810:
                case 0x6820:
                case 0x6830:
                    return Architecture::AMD_GCN1;
                case 0x6640:
                case 0x6650:
                case 0x67A0:
                case 0x67B0:
                case 0x9830:
                case 0x9850:
                    return Architecture::AMD_GCN2;
                case 0x6900:
                case 0x6920:
                case 0x6930:
                case 0x7300:
                case 0x9870:
                case 0x98E0:
                    return Architecture::AMD_GCN3;
                case 0x67C0:
                case 0x67D0:
                case 0x67E0:
                case 0x67F0:
                case 0x6980:
                case 0x6990:
                    return Architecture::AMD_GCN4;
                case 0x66A0:
                case 0x6860:
                case 0x6870:
                case 0x6940:
                case 0x69A0:
                    return Architecture::AMD_GCN5;
                case 0x7310:
                case 0x7340:
                case 0x7360:
                    return Architecture::AMD_RDNA1;
                case 0x73A0:
                case 0x73B0:
                case 0x73D0:
                case 0x73E0:
                case 0x73F0:
                    return Architecture::AMD_RDNA2;
            }
        } break;
        case kVendorID_ARM: {
            switch (deviceId & 0xF0000000) {
                case 0x00000000:
                    return Architecture::ARM_Midgard;
                case 0x60000000:
                case 0x70000000:
                    return Architecture::ARM_Bifrost;
                case 0x90000000:
                case 0xA0000000:
                    return Architecture::ARM_Valhall;
            }
        } break;
        case kVendorID_Google: {
            switch (deviceId) {
                case 0xC0DE:
                    return Architecture::Google_Swiftshader;
            }
        } break;
        case kVendorID_Intel: {
            switch (deviceId & 0xFF00) {
                case 0x0100:
                case 0x0400:
                case 0x0A00:
                case 0x0D00:
                case 0x0F00:
                    return Architecture::Intel_Gen7;
                case 0x1600:
                case 0x2200:
                    return Architecture::Intel_Gen8;
                case 0x1900:
                case 0x3100:
                case 0x3E00:
                case 0x5A00:
                case 0x5900:
                case 0x9B00:
                    return Architecture::Intel_Gen9;
                case 0x8A00:
                    return Architecture::Intel_Gen11;
                case 0x4600:
                case 0x4C00:
                case 0x4900:
                case 0x9A00:
                case 0xA700:
                    return Architecture::Intel_Gen12LP;
                case 0x4F00:
                case 0x5600:
                    return Architecture::Intel_Gen12HP;
            }
        } break;
        case kVendorID_Microsoft: {
            switch (deviceId) {
                case 0x8c:
                    return Architecture::Microsoft_WARP;
            }
        } break;
        case kVendorID_Nvidia: {
            switch (deviceId & 0xFF00) {
                case 0x0D00:
                    return Architecture::Nvidia_Fermi;
                case 0x0F00:
                case 0x1000:
                case 0x1100:
                case 0x1200:
                    return Architecture::Nvidia_Kepler;
                case 0x1300:
                case 0x1400:
                case 0x1600:
                case 0x1700:
                    return Architecture::Nvidia_Maxwell;
                case 0x1500:
                case 0x1B00:
                case 0x1C00:
                case 0x1D00:
                    return Architecture::Nvidia_Pascal;
                case 0x1E00:
                case 0x1F00:
                case 0x2100:
                    return Architecture::Nvidia_Turing;
                case 0x2200:
                case 0x2400:
                case 0x2500:
                    return Architecture::Nvidia_Ampere;
            }
        } break;
        case kVendorID_Qualcomm: {
            switch (deviceId & 0xFF000000) {
                case 0x04000000:
                    return Architecture::Qualcomm_Adreno4xx;
                case 0x05000000:
                    return Architecture::Qualcomm_Adreno5xx;
                case 0x06000000:
                    return Architecture::Qualcomm_Adreno6xx;
                case 0x07000000:
                    return Architecture::Qualcomm_Adreno7xx;
            }
        } break;
        case kVendorID_Samsung: {
            switch (deviceId) {
                case 0x73A0:
                    return Architecture::Samsung_RDNA2;
            }
        } break;
    }

    return Architecture::Unknown;
}


}  // namespace

// Vendor checks
bool IsAMD(PCIVendorID vendorId) {
    return vendorId == kVendorID_AMD;
}
bool IsApple(PCIVendorID vendorId) {
    return vendorId == kVendorID_Apple;
}
bool IsARM(PCIVendorID vendorId) {
    return vendorId == kVendorID_ARM;
}
bool IsGoogle(PCIVendorID vendorId) {
    return vendorId == kVendorID_Google;
}
bool IsImgTec(PCIVendorID vendorId) {
    return vendorId == kVendorID_ImgTec;
}
bool IsIntel(PCIVendorID vendorId) {
    return vendorId == kVendorID_Intel;
}
bool IsMesa(PCIVendorID vendorId) {
    return vendorId == kVendorID_Mesa;
}
bool IsMicrosoft(PCIVendorID vendorId) {
    return vendorId == kVendorID_Microsoft;
}
bool IsNvidia(PCIVendorID vendorId) {
    return vendorId == kVendorID_Nvidia;
}
bool IsQualcomm(PCIVendorID vendorId) {
    return vendorId == kVendorID_Qualcomm;
}
bool IsSamsung(PCIVendorID vendorId) {
    return vendorId == kVendorID_Samsung;
}

// Architecture checks

// AMD architectures
bool IsAMDGCN2(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_GCN2;
}
bool IsAMDGCN5(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_GCN5;
}
bool IsAMDRDNA2(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_RDNA2;
}
bool IsAMDGCN1(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_GCN1;
}
bool IsAMDGCN3(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_GCN3;
}
bool IsAMDGCN4(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_GCN4;
}
bool IsAMDRDNA1(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::AMD_RDNA1;
}
// ARM architectures
bool IsARMMidgard(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::ARM_Midgard;
}
bool IsARMBifrost(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::ARM_Bifrost;
}
bool IsARMValhall(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::ARM_Valhall;
}
// Google architectures
bool IsGoogleSwiftshader(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Google_Swiftshader;
}
// Intel architectures
bool IsIntelGen7(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen7;
}
bool IsIntelGen8(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen8;
}
bool IsIntelGen9(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen9;
}
bool IsIntelGen11(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen11;
}
bool IsIntelGen12LP(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen12LP;
}
bool IsIntelGen12HP(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Intel_Gen12HP;
}
// Microsoft architectures
bool IsMicrosoftWARP(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Microsoft_WARP;
}
// Nvidia architectures
bool IsNvidiaFermi(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Fermi;
}
bool IsNvidiaKepler(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Kepler;
}
bool IsNvidiaMaxwell(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Maxwell;
}
bool IsNvidiaPascal(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Pascal;
}
bool IsNvidiaTuring(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Turing;
}
bool IsNvidiaAmpere(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Nvidia_Ampere;
}
// Qualcomm architectures
bool IsQualcommAdreno4xx(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Qualcomm_Adreno4xx;
}
bool IsQualcommAdreno5xx(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Qualcomm_Adreno5xx;
}
bool IsQualcommAdreno6xx(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Qualcomm_Adreno6xx;
}
bool IsQualcommAdreno7xx(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Qualcomm_Adreno7xx;
}
// Samsung architectures
bool IsSamsungRDNA2(PCIVendorID vendorId, PCIDeviceID deviceId) {
    return GetArchitecture(vendorId, deviceId) == Architecture::Samsung_RDNA2;
}

// GPUAdapterInfo fields
std::string GetVendorName(PCIVendorID vendorId) {
    switch(vendorId) {
        case kVendorID_AMD: return "amd";
        case kVendorID_Apple: return "apple";
        case kVendorID_ARM: return "arm";
        case kVendorID_Google: return "google";
        case kVendorID_ImgTec: return "img-tec";
        case kVendorID_Intel: return "intel";
        case kVendorID_Mesa: return "mesa";
        case kVendorID_Microsoft: return "microsoft";
        case kVendorID_Nvidia: return "nvidia";
        case kVendorID_Qualcomm: return "qualcomm";
        case kVendorID_Samsung: return "samsung";
    }

    return "";
}

std::string GetArchitectureName(PCIVendorID vendorId, PCIDeviceID deviceId) {
    Architecture arch = GetArchitecture(vendorId, deviceId);
    switch(arch) {
        case Architecture::Unknown:
            return "";
        case Architecture::AMD_GCN2:
            return "gcn-2";
        case Architecture::AMD_GCN5:
            return "gcn-5";
        case Architecture::AMD_RDNA2:
            return "rdna-2";
        case Architecture::AMD_GCN1:
            return "gcn-1";
        case Architecture::AMD_GCN3:
            return "gcn-3";
        case Architecture::AMD_GCN4:
            return "gcn-4";
        case Architecture::AMD_RDNA1:
            return "rdna-1";
        case Architecture::ARM_Midgard:
            return "midgard";
        case Architecture::ARM_Bifrost:
            return "bifrost";
        case Architecture::ARM_Valhall:
            return "valhall";
        case Architecture::Google_Swiftshader:
            return "swiftshader";
        case Architecture::Intel_Gen7:
            return "gen-7";
        case Architecture::Intel_Gen8:
            return "gen-8";
        case Architecture::Intel_Gen9:
            return "gen-9";
        case Architecture::Intel_Gen11:
            return "gen-11";
        case Architecture::Intel_Gen12LP:
            return "gen-12lp";
        case Architecture::Intel_Gen12HP:
            return "gen-12hp";
        case Architecture::Microsoft_WARP:
            return "warp";
        case Architecture::Nvidia_Fermi:
            return "fermi";
        case Architecture::Nvidia_Kepler:
            return "kepler";
        case Architecture::Nvidia_Maxwell:
            return "maxwell";
        case Architecture::Nvidia_Pascal:
            return "pascal";
        case Architecture::Nvidia_Turing:
            return "turing";
        case Architecture::Nvidia_Ampere:
            return "ampere";
        case Architecture::Qualcomm_Adreno4xx:
            return "adreno-4xx";
        case Architecture::Qualcomm_Adreno5xx:
            return "adreno-5xx";
        case Architecture::Qualcomm_Adreno6xx:
            return "adreno-6xx";
        case Architecture::Qualcomm_Adreno7xx:
            return "adreno-7xx";
        case Architecture::Samsung_RDNA2:
            return "rdna-2";
    }

    return "";
}

}  // namespace dawn::gpu_info
