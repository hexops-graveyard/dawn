
#include "dawn/native/CacheKey.h"
#include "dawn/native/dawn_platform.h"

#include <cstring>

namespace dawn::native {

//
// Cache key writers for wgpu structures used in caching.
//


template <>
void stream::Stream<AdapterProperties>::Write(stream::Sink* sink, const AdapterProperties& t) {

    StreamIn(sink, t.vendorID);
    StreamIn(sink, Iterable(t.vendorName, strlen(t.vendorName)));
    StreamIn(sink, Iterable(t.architecture, strlen(t.architecture)));
    StreamIn(sink, t.deviceID);
    StreamIn(sink, Iterable(t.name, strlen(t.name)));
    StreamIn(sink, Iterable(t.driverDescription, strlen(t.driverDescription)));
    StreamIn(sink, t.adapterType);
    StreamIn(sink, t.backendType);
}

template <>
void stream::Stream<DawnCacheDeviceDescriptor>::Write(stream::Sink* sink, const DawnCacheDeviceDescriptor& t) {

    StreamIn(sink, Iterable(t.isolationKey, strlen(t.isolationKey)));
}

} // namespace dawn::native
