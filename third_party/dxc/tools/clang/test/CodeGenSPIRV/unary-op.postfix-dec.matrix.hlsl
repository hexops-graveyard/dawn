// RUN: %dxc -T ps_6_0 -E main

// CHECK: [[v2f1:%\d+]] = OpConstantComposite %v2float %float_1 %float_1
// CHECK: [[v3f1:%\d+]] = OpConstantComposite %v3float %float_1 %float_1 %float_1
// CHECK: [[v3i1:%\d+]] = OpConstantComposite %v3int %int_1 %int_1 %int_1

void main() {
// CHECK-LABEL: %bb_entry = OpLabel

    // 1x1
    float1x1 a, b;
// CHECK:      [[a0:%\d+]] = OpLoad %float %a
// CHECK-NEXT: [[a1:%\d+]] = OpFSub %float [[a0]] %float_1
// CHECK-NEXT: OpStore %a [[a1]]
// CHECK-NEXT: OpStore %b [[a0]]
    b = a--;

    // Mx1
    float2x1 c, d;
// CHECK-NEXT: [[c0:%\d+]] = OpLoad %v2float %c
// CHECK-NEXT: [[c1:%\d+]] = OpFSub %v2float [[c0]] [[v2f1]]
// CHECK-NEXT: OpStore %c [[c1]]
// CHECK-NEXT: OpStore %d [[c0]]
    d = c--;

    // 1xN
    float1x3 e, f;
// CHECK-NEXT: [[e0:%\d+]] = OpLoad %v3float %e
// CHECK-NEXT: [[e1:%\d+]] = OpFSub %v3float [[e0]] [[v3f1]]
// CHECK-NEXT: OpStore %e [[e1]]
// CHECK-NEXT: OpStore %f [[e0]]
    f = e--;

    // MxN
    float2x3 g, h;
// CHECK-NEXT: [[g0:%\d+]] = OpLoad %mat2v3float %g
// CHECK-NEXT: [[g0v0:%\d+]] = OpCompositeExtract %v3float [[g0]] 0
// CHECK-NEXT: [[dec0:%\d+]] = OpFSub %v3float [[g0v0]] [[v3f1]]
// CHECK-NEXT: [[g0v1:%\d+]] = OpCompositeExtract %v3float [[g0]] 1
// CHECK-NEXT: [[dec1:%\d+]] = OpFSub %v3float [[g0v1]] [[v3f1]]
// CHECK-NEXT: [[g1:%\d+]] = OpCompositeConstruct %mat2v3float [[dec0]] [[dec1]]
// CHECK-NEXT: OpStore %g [[g1]]
// CHECK-NEXT: OpStore %h [[g0]]
    h = g--;

// CHECK:         [[i:%\d+]] = OpLoad %_arr_v3int_uint_2 %i
// CHECK-NEXT:   [[i0:%\d+]] = OpCompositeExtract %v3int [[i]] 0
// CHECK-NEXT: [[dec0:%\d+]] = OpISub %v3int [[i0]] [[v3i1]]
// CHECK-NEXT:   [[i1:%\d+]] = OpCompositeExtract %v3int [[i]] 1
// CHECK-NEXT: [[dec1:%\d+]] = OpISub %v3int [[i1]] [[v3i1]]
// CHECK-NEXT:  [[dec:%\d+]] = OpCompositeConstruct %_arr_v3int_uint_2 [[dec0]] [[dec1]]
// CHECK-NEXT: OpStore %i [[dec]]
// CHECK-NEXT: OpStore %j [[i]]
    int2x3 i, j;
    j = i--;

// Note: This postfix decrement is not allowed with boolean matrix type (by the front-end).
}
