// RUN: %dxc -T cs_6_0 -E main -O3

// CHECK:      [[val:%\d+]] = OpConstantComposite %v4float %float_0 %float_0 %float_0 %float_0
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_v4float %gRWSBuffer
// CHECK-NEXT:                OpStore [[ptr]] [[val]]

struct S {
  float4 f;
};

int i;

RWStructuredBuffer<S> gRWSBuffer;

static RWStructuredBuffer<S> sRWSBuffer = gRWSBuffer;

[numthreads(1,1,1)]
void main() {
  sRWSBuffer[i].f = 0.0;
}
