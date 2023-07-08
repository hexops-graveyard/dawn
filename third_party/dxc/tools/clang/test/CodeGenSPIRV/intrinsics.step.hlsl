// RUN: %dxc -T vs_6_0 -E main

// CHECK:      [[glsl:%\d+]] = OpExtInstImport "GLSL.std.450"

void main() {
  float result;
  float2 result2;
  float3 result3;
  float4 result4;
  float2x3 result2x3;

// CHECK: {{%\d+}} = OpExtInst %float [[glsl]] Step {{%\d+}} {{%\d+}}
  float a1,a2;
  result = step(a1,a2);

// CHECK: {{%\d+}} = OpExtInst %float [[glsl]] Step {{%\d+}} {{%\d+}}
  float1 b1,b2;
  result = step(b1,b2);

// CHECK: {{%\d+}} = OpExtInst %v3float [[glsl]] Step {{%\d+}} {{%\d+}}
  float3 c1,c2;
  result3 = step(c1,c2);

// CHECK: {{%\d+}} = OpExtInst %float [[glsl]] Step {{%\d+}} {{%\d+}}
  float1x1 d1,d2;
  result = step(d1,d2);

// CHECK: {{%\d+}} = OpExtInst %v2float [[glsl]] Step {{%\d+}} {{%\d+}}
  float1x2 e1,e2;
  result2 = step(e1,e2);

// CHECK: {{%\d+}} = OpExtInst %v4float [[glsl]] Step {{%\d+}} {{%\d+}}
  float4x1 f1,f2;
  result4 = step(f1,f2);

// CHECK:      [[g1:%\d+]] = OpLoad %mat2v3float %g1
// CHECK-NEXT: [[g2:%\d+]] = OpLoad %mat2v3float %g2
// CHECK-NEXT: [[g1_row0:%\d+]] = OpCompositeExtract %v3float [[g1]] 0
// CHECK-NEXT: [[g2_row0:%\d+]] = OpCompositeExtract %v3float [[g2]] 0
// CHECK-NEXT: [[result_row0:%\d+]] = OpExtInst %v3float [[glsl]] Step [[g1_row0]] [[g2_row0]]
// CHECK-NEXT: [[g1_row1:%\d+]] = OpCompositeExtract %v3float [[g1]] 1
// CHECK-NEXT: [[g2_row1:%\d+]] = OpCompositeExtract %v3float [[g2]] 1
// CHECK-NEXT: [[result_row1:%\d+]] = OpExtInst %v3float [[glsl]] Step [[g1_row1]] [[g2_row1]]
// CHECK-NEXT: {{%\d+}} = OpCompositeConstruct %mat2v3float [[result_row0]] [[result_row1]]
  float2x3 g1,g2;
  result2x3 = step(g1,g2);
}
