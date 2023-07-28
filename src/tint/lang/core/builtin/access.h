// Copyright 2020 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/lang/core/builtin/access.h.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_CORE_BUILTIN_ACCESS_H_
#define SRC_TINT_LANG_CORE_BUILTIN_ACCESS_H_

#include "src/tint/utils/text/string_stream.h"

namespace tint::builtin {

/// Address space of a given pointer.
enum class Access {
    kUndefined,
    kRead,
    kReadWrite,
    kWrite,
};

/// @param out the stream to write to
/// @param value the Access
/// @returns `out` so calls can be chained
StringStream& operator<<(StringStream& out, Access value);

/// ParseAccess parses a Access from a string.
/// @param str the string to parse
/// @returns the parsed enum, or Access::kUndefined if the string could not be parsed.
Access ParseAccess(std::string_view str);

constexpr const char* kAccessStrings[] = {
    "read",
    "read_write",
    "write",
};

}  // namespace tint::builtin

#endif  // SRC_TINT_LANG_CORE_BUILTIN_ACCESS_H_
