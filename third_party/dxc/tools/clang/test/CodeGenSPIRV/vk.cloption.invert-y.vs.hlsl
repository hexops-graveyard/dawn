// RUN: %dxc -T vs_6_0 -E main -fvk-invert-y

float4 main(float4 a : A) : SV_Position {
    return a;
}

// CHECK:         [[a:%\d+]] = OpFunctionCall %v4float %src_main %param_var_a
// CHECK-NEXT: [[oldY:%\d+]] = OpCompositeExtract %float [[a]] 1
// CHECK-NEXT: [[newY:%\d+]] = OpFNegate %float [[oldY]]
// CHECK-NEXT:  [[pos:%\d+]] = OpCompositeInsert %v4float [[newY]] [[a]] 1
// CHECK-NEXT:                 OpStore %gl_Position [[pos]]
