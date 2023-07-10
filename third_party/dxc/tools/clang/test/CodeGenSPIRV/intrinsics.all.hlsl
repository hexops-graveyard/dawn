// RUN: %dxc -T vs_6_0 -E main

// According to HLSL reference:
// The 'all' function can only operate on int, bool, float,
// vector of these scalars, and matrix of these scalars.

// CHECK:   [[v4int_0:%\d+]] = OpConstantComposite %v4int %int_0 %int_0 %int_0 %int_0
// CHECK:  [[v4uint_0:%\d+]] = OpConstantComposite %v4uint %uint_0 %uint_0 %uint_0 %uint_0
// CHECK: [[v4float_0:%\d+]] = OpConstantComposite %v4float %float_0 %float_0 %float_0 %float_0
// CHECK: [[v3float_0:%\d+]] = OpConstantComposite %v3float %float_0 %float_0 %float_0
// CHECK: [[v2float_0:%\d+]] = OpConstantComposite %v2float %float_0 %float_0
// CHECK:   [[v3int_0:%\d+]] = OpConstantComposite %v3int %int_0 %int_0 %int_0

void main() {
    bool result;

    // CHECK:      [[a:%\d+]] = OpLoad %int %a
    // CHECK-NEXT: [[all_int:%\d+]] = OpINotEqual %bool [[a]] %int_0
    // CHECK-NEXT: OpStore %result [[all_int]]
    int a;
    result = all(a);

    // CHECK-NEXT: [[b:%\d+]] = OpLoad %uint %b
    // CHECK-NEXT: [[all_uint:%\d+]] = OpINotEqual %bool [[b]] %uint_0
    // CHECK-NEXT: OpStore %result [[all_uint]]
    uint b;
    result = all(b);

    // CHECK-NEXT: [[c:%\d+]] = OpLoad %bool %c
    // CHECK-NEXT: OpStore %result [[c]]
    bool c;
    result = all(c);

    // CHECK-NEXT: [[d:%\d+]] = OpLoad %float %d
    // CHECK-NEXT: [[all_float:%\d+]] = OpFOrdNotEqual %bool [[d]] %float_0
    // CHECK-NEXT: OpStore %result [[all_float]]
    float d;
    result = all(d);

    // CHECK-NEXT: [[e:%\d+]] = OpLoad %int %e
    // CHECK-NEXT: [[all_int1:%\d+]] = OpINotEqual %bool [[e]] %int_0
    // CHECK-NEXT: OpStore %result [[all_int1]]
    int1 e;
    result = all(e);

    // CHECK-NEXT: [[f:%\d+]] = OpLoad %uint %f
    // CHECK-NEXT: [[all_uint1:%\d+]] = OpINotEqual %bool [[f]] %uint_0
    // CHECK-NEXT: OpStore %result [[all_uint1]]
    uint1 f;
    result = all(f);

    // CHECK-NEXT: [[g:%\d+]] = OpLoad %bool %g
    // CHECK-NEXT: OpStore %result [[g]]
    bool1 g;
    result = all(g);

    // CHECK-NEXT: [[h:%\d+]] = OpLoad %float %h
    // CHECK-NEXT: [[all_float1:%\d+]] = OpFOrdNotEqual %bool [[h]] %float_0
    // CHECK-NEXT: OpStore %result [[all_float1]]
    float1 h;
    result = all(h);

    // CHECK-NEXT: [[i:%\d+]] = OpLoad %v4int %i
    // CHECK-NEXT: [[v4int_to_bool:%\d+]] = OpINotEqual %v4bool [[i]] [[v4int_0]]
    // CHECK-NEXT: [[all_int4:%\d+]] = OpAll %bool [[v4int_to_bool]]
    // CHECK-NEXT: OpStore %result [[all_int4]]
    int4 i;
    result = all(i);

    // CHECK-NEXT: [[j:%\d+]] = OpLoad %v4uint %j
    // CHECK-NEXT: [[v4uint_to_bool:%\d+]] = OpINotEqual %v4bool [[j]] [[v4uint_0]]
    // CHECK-NEXT: [[all_uint4:%\d+]] = OpAll %bool [[v4uint_to_bool]]
    // CHECK-NEXT: OpStore %result [[all_uint4]]
    uint4 j;
    result = all(j);

    // CHECK-NEXT: [[k:%\d+]] = OpLoad %v4bool %k
    // CHECK-NEXT: [[all_bool4:%\d+]] = OpAll %bool [[k]]
    // CHECK-NEXT: OpStore %result [[all_bool4]]
    bool4 k;
    result = all(k);

    // CHECK-NEXT: [[l:%\d+]] = OpLoad %v4float %l
    // CHECK-NEXT: [[v4float_to_bool:%\d+]] = OpFOrdNotEqual %v4bool [[l]] [[v4float_0]]
    // CHECK-NEXT: [[all_float4:%\d+]] = OpAll %bool [[v4float_to_bool]]
    // CHECK-NEXT: OpStore %result [[all_float4]]
    float4 l;
    result = all(l);

    // CHECK-NEXT: [[m:%\d+]] = OpLoad %float %m
    // CHECK-NEXT: [[mat1x1_to_bool:%\d+]] = OpFOrdNotEqual %bool [[m]] %float_0
    // CHECK-NEXT: OpStore %result [[mat1x1_to_bool]]
    float1x1 m;
    result = all(m);

    // CHECK-NEXT: [[n:%\d+]] = OpLoad %v3float %n
    // CHECK-NEXT: [[mat1x3_to_bool:%\d+]] = OpFOrdNotEqual %v3bool [[n]] [[v3float_0]]
    // CHECK-NEXT: [[all_mat1x3:%\d+]] = OpAll %bool [[mat1x3_to_bool]]
    // CHECK-NEXT: OpStore %result [[all_mat1x3]]
    float1x3 n;
    result = all(n);

    // CHECK-NEXT: [[o:%\d+]] = OpLoad %v2float %o
    // CHECK-NEXT: [[mat2x1_to_bool:%\d+]] = OpFOrdNotEqual %v2bool [[o]] [[v2float_0]]
    // CHECK-NEXT: [[all_mat2x1:%\d+]] = OpAll %bool [[mat2x1_to_bool]]
    // CHECK-NEXT: OpStore %result [[all_mat2x1]]
    float2x1 o;
    result = all(o);

    // CHECK-NEXT: [[p:%\d+]] = OpLoad %mat3v4float %p
    // CHECK-NEXT: [[row0:%\d+]] = OpCompositeExtract %v4float [[p]] 0
    // CHECK-NEXT: [[row0_to_bool_vec:%\d+]] = OpFOrdNotEqual %v4bool [[row0]] [[v4float_0]]
    // CHECK-NEXT: [[all_row0:%\d+]] = OpAll %bool [[row0_to_bool_vec]]
    // CHECK-NEXT: [[row1:%\d+]] = OpCompositeExtract %v4float [[p]] 1
    // CHECK-NEXT: [[row1_to_bool_vec:%\d+]] = OpFOrdNotEqual %v4bool [[row1]] [[v4float_0]]
    // CHECK-NEXT: [[all_row1:%\d+]] = OpAll %bool [[row1_to_bool_vec]]
    // CHECK-NEXT: [[row2:%\d+]] = OpCompositeExtract %v4float [[p]] 2
    // CHECK-NEXT: [[row2_to_bool_vec:%\d+]] = OpFOrdNotEqual %v4bool [[row2]] [[v4float_0]]
    // CHECK-NEXT: [[all_row2:%\d+]] = OpAll %bool [[row2_to_bool_vec]]
    // CHECK-NEXT: [[all_rows:%\d+]] = OpCompositeConstruct %v3bool [[all_row0]] [[all_row1]] [[all_row2]]
    // CHECK-NEXT: [[all_mat3x4:%\d+]] = OpAll %bool [[all_rows]]
    // CHECK-NEXT: OpStore %result [[all_mat3x4]]
    float3x4 p;
    result = all(p);

// CHECK:              [[q:%\d+]] = OpLoad %_arr_v3int_uint_2 %q
// CHECK-NEXT:      [[row0:%\d+]] = OpCompositeExtract %v3int [[q]] 0
// CHECK-NEXT: [[row0_bool:%\d+]] = OpINotEqual %v3bool [[row0]] [[v3int_0]]
// CHECK-NEXT:  [[row0_all:%\d+]] = OpAll %bool [[row0_bool]]
// CHECK-NEXT:      [[row1:%\d+]] = OpCompositeExtract %v3int [[q]] 1
// CHECK-NEXT: [[row1_bool:%\d+]] = OpINotEqual %v3bool [[row1]] [[v3int_0]]
// CHECK-NEXT:  [[row1_all:%\d+]] = OpAll %bool [[row1_bool]]
// CHECK-NEXT:  [[all_rows:%\d+]] = OpCompositeConstruct %v2bool [[row0_all]] [[row1_all]]
// CHECK-NEXT:           {{%\d+}} = OpAll %bool [[all_rows]]
    int2x3 q;
    result = all(q);
}
