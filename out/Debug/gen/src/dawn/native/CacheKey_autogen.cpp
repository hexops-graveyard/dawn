
#include "dawn/native/CacheKey.h"
#include "dawn/native/dawn_platform.h"

#include <cstring>

namespace dawn::native {

//
// Cache key serializers for wgpu structures used in caching.
//


template <>
void CacheKeySerializer<AdapterProperties>::Serialize(CacheKey* key, const AdapterProperties& t) {

    key->Record(t.vendorID);
    key->Record(t.deviceID);
    key->RecordIterable(t.name, strlen(t.name));
    key->RecordIterable(t.driverDescription, strlen(t.driverDescription));
    key->Record(t.adapterType);
    key->Record(t.backendType);
}

template <>
void CacheKeySerializer<DawnCacheDeviceDescriptor>::Serialize(CacheKey* key, const DawnCacheDeviceDescriptor& t) {

    key->RecordIterable(t.isolationKey, strlen(t.isolationKey));
}

} // namespace dawn::native
