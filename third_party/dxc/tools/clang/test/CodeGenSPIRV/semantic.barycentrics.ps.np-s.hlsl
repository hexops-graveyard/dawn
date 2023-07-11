// RUN: %dxc -T ps_6_1 -E main

// CHECK:      OpExtension "SPV_KHR_fragment_shader_barycentric"

// CHECK:      OpEntryPoint Fragment
// CHECK-SAME: [[bary:%\d+]]

// CHECK:      OpDecorate [[bary]] BuiltIn BaryCoordNoPerspKHR
// CHECK:      OpDecorate [[bary]] Sample

// CHECK:      [[bary]] = OpVariable %_ptr_Input_v3float Input

float4 main(noperspective sample float3 bary : SV_Barycentrics) : SV_Target {
    return float4(bary, 1.0);
// CHECK:      %param_var_bary = OpVariable %_ptr_Function_v3float Function
// CHECK-NEXT:     [[c2:%\d+]] = OpLoad %v3float [[bary]]
// CHECK-NEXT:      [[x:%\d+]] = OpCompositeExtract %float [[c2]] 0
// CHECK-NEXT:      [[y:%\d+]] = OpCompositeExtract %float [[c2]] 1
// CHECK-NEXT:     [[xy:%\d+]] = OpFAdd %float [[x]] [[y]]
// CHECK-NEXT:      [[z:%\d+]] = OpFSub %float %float_1 [[xy]]
// CHECK-NEXT:     [[c3:%\d+]] = OpCompositeConstruct %v3float [[x]] [[y]] [[z]]
// CHECK-NEXT:                   OpStore %param_var_bary [[c3]]
}
