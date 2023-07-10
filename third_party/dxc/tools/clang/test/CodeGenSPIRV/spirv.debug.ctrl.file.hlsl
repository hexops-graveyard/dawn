// RUN: %dxc -T ps_6_1 -E main -fspv-target-env=vulkan1.1 -fspv-debug=file -Zi

// Have file path
// CHECK:      [[file:%\d+]] = OpString
// CHECK-SAME: spirv.debug.ctrl.file.hlsl
// CHECK:      OpSource HLSL 610 [[file]]
// No source code
// CHECK-NOT:  float4 main(uint val
// No tool
// CHECK-NOT: OpModuleProcessed
// No line
// CHECK-NOT: OpLine

float4 main(uint val : A) : SV_Target {
  uint a = reversebits(val);
  return a;
}
