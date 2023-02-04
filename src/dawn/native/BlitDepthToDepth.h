// Copyright 2023 The Dawn Authors
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

#ifndef SRC_DAWN_NATIVE_BLITDEPTHTODEPTH_H_
#define SRC_DAWN_NATIVE_BLITDEPTHTODEPTH_H_

#include "dawn/native/Error.h"

namespace dawn::native {

class DeviceBase;
class CommandEncoder;
struct TextureCopy;
struct Extent3D;

MaybeError BlitDepthToDepth(DeviceBase* device,
                            CommandEncoder* commandEncoder,
                            const TextureCopy& src,
                            const TextureCopy& dst,
                            const Extent3D& copyExtent);

}  // namespace dawn::native

#endif  // SRC_DAWN_NATIVE_BLITDEPTHTODEPTH_H_
