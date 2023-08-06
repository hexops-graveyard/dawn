
#include "dawn/native/CacheKey.h"
#include "dawn/native/dawn_platform.h"

#include <cstring>

namespace dawn::native {




// Custom stream operator for special bool type.
template <>
void stream::Stream<wgpu::Bool>::Write(stream::Sink* sink, const wgpu::Bool& t) {
    StreamIn(sink, static_cast<bool>(t));
}

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

    StreamIn(sink, t.compatibilityMode);

}

template <>
void stream::Stream<DawnCacheDeviceDescriptor>::Write(stream::Sink* sink, const DawnCacheDeviceDescriptor& t) {

    StreamIn(sink, Iterable(t.isolationKey, strlen(t.isolationKey)));

}

template <>
MaybeError stream::Stream<Extent3D>::Read(stream::Source* source, Extent3D* t) {

    DAWN_TRY(StreamOut(source, &t->width));

    DAWN_TRY(StreamOut(source, &t->height));

    DAWN_TRY(StreamOut(source, &t->depthOrArrayLayers));

    return {};
}
template <>
void stream::Stream<Extent3D>::Write(stream::Sink* sink, const Extent3D& t) {

    StreamIn(sink, t.width);

    StreamIn(sink, t.height);

    StreamIn(sink, t.depthOrArrayLayers);

}

} // namespace dawn::native
