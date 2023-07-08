// RUN: %dxc -T hs_6_1 -E main

// Test: Both entry point and PCF Takes ViewID

// CHECK:      OpCapability MultiView
// CHECK:      OpExtension "SPV_KHR_multiview"

// CHECK:      OpEntryPoint TessellationControl
// CHECK-SAME: [[viewindex:%\d+]]

// CHECK:      OpDecorate [[viewindex]] BuiltIn ViewIndex

// CHECK:      [[pcfType:%\d+]] = OpTypeFunction %HsPcfOut %_ptr_Function_uint
// CHECK:         [[viewindex]] = OpVariable %_ptr_Input_uint Input

#define NumOutPoints 2

struct HsCpIn {
    int foo : FOO;
};

struct HsCpOut {
    int bar : BAR;
};

struct HsPcfOut {
  float tessOuter[4] : SV_TessFactor;
  float tessInner[2] : SV_InsideTessFactor;
};

// Patch Constant Function
HsPcfOut pcf(uint viewid : SV_ViewID) {
  HsPcfOut output;
  output = (HsPcfOut)0;
  return output;
}

[domain("quad")]
[partitioning("fractional_odd")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(NumOutPoints)]
[patchconstantfunc("pcf")]
HsCpOut main(InputPatch<HsCpIn, NumOutPoints> patch,
             uint id : SV_OutputControlPointID,
             uint viewid : SV_ViewID) {
    HsCpOut output;
    output.bar = viewid;
    return output;
// CHECK:             %main = OpFunction %void None {{%\d+}}
// CHECK: %param_var_viewid = OpVariable %_ptr_Function_uint Function

// CHECK:      [[val:%\d+]] = OpLoad %uint [[viewindex]]
// CHECK:                     OpStore %param_var_viewid [[val]]
// CHECK:          {{%\d+}} = OpFunctionCall %HsPcfOut %pcf %param_var_viewid

// CHECK:              %pcf = OpFunction %HsPcfOut None [[pcfType]]
// CHECK:           %viewid = OpFunctionParameter %_ptr_Function_uint
}
