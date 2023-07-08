// RUN: %dxc -T vs_6_0 -E main

// According to HLSL reference:
// The 'exp2' function can only operate on float, vector of float, and matrix of float.

// CHECK:      [[glsl:%\d+]] = OpExtInstImport "GLSL.std.450"

void main() {
  float result;
  float2 result2;
  float3 result3;
  float4 result4;
  float3x2 result3x2;

// CHECK:      [[a:%\d+]] = OpLoad %float %a
// CHECK-NEXT: [[exp2_a:%\d+]] = OpExtInst %float [[glsl]] Exp2 [[a]]
// CHECK-NEXT: OpStore %result [[exp2_a]]
  float a;
  result = exp2(a);

// CHECK-NEXT: [[b:%\d+]] = OpLoad %float %b
// CHECK-NEXT: [[exp2_b:%\d+]] = OpExtInst %float [[glsl]] Exp2 [[b]]
// CHECK-NEXT: OpStore %result [[exp2_b]]
  float1 b;
  result = exp2(b);

// CHECK-NEXT: [[c:%\d+]] = OpLoad %v3float %c
// CHECK-NEXT: [[exp2_c:%\d+]] = OpExtInst %v3float [[glsl]] Exp2 [[c]]
// CHECK-NEXT: OpStore %result3 [[exp2_c]]
  float3 c;
  result3 = exp2(c);

// CHECK-NEXT: [[d:%\d+]] = OpLoad %float %d
// CHECK-NEXT: [[exp2_d:%\d+]] = OpExtInst %float [[glsl]] Exp2 [[d]]
// CHECK-NEXT: OpStore %result [[exp2_d]]
  float1x1 d;
  result = exp2(d);

// CHECK-NEXT: [[e:%\d+]] = OpLoad %v2float %e
// CHECK-NEXT: [[exp2_e:%\d+]] = OpExtInst %v2float [[glsl]] Exp2 [[e]]
// CHECK-NEXT: OpStore %result2 [[exp2_e]]
  float1x2 e;
  result2 = exp2(e);

// CHECK-NEXT: [[f:%\d+]] = OpLoad %v4float %f
// CHECK-NEXT: [[exp2_f:%\d+]] = OpExtInst %v4float [[glsl]] Exp2 [[f]]
// CHECK-NEXT: OpStore %result4 [[exp2_f]]
  float4x1 f;
  result4 = exp2(f);

// CHECK-NEXT: [[g:%\d+]] = OpLoad %mat3v2float %g
// CHECK-NEXT: [[g_row0:%\d+]] = OpCompositeExtract %v2float [[g]] 0
// CHECK-NEXT: [[exp2_g_row0:%\d+]] = OpExtInst %v2float [[glsl]] Exp2 [[g_row0]]
// CHECK-NEXT: [[g_row1:%\d+]] = OpCompositeExtract %v2float [[g]] 1
// CHECK-NEXT: [[exp2_g_row1:%\d+]] = OpExtInst %v2float [[glsl]] Exp2 [[g_row1]]
// CHECK-NEXT: [[g_row2:%\d+]] = OpCompositeExtract %v2float [[g]] 2
// CHECK-NEXT: [[exp2_g_row2:%\d+]] = OpExtInst %v2float [[glsl]] Exp2 [[g_row2]]
// CHECK-NEXT: [[exp2_matrix:%\d+]] = OpCompositeConstruct %mat3v2float [[exp2_g_row0]] [[exp2_g_row1]] [[exp2_g_row2]]
// CHECK-NEXT: OpStore %result3x2 [[exp2_matrix]]
  float3x2 g;
  result3x2 = exp2(g);
}
