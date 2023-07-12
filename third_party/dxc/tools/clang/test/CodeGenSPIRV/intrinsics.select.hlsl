// RUN: %dxc -T ps_6_0 -E main -HV 2021
// RUN: %dxc -T ps_6_0 -E main -HV 2018

// CHECK: [[v3i0:%\d+]] = OpConstantComposite %v3int %int_0 %int_0 %int_0

uint foo() { return 1; }
float bar() { return 3.0; }
uint zoo();

void main() {
  // CHECK-LABEL: %bb_entry = OpLabel

  // CHECK: %temp_var_ternary = OpVariable %_ptr_Function_mat2v3float Function
  // CHECK: %temp_var_ternary_0 = OpVariable %_ptr_Function_mat2v3float Function

  bool b0;
  int m, n, o;
  // Plain assign (scalar)
  // CHECK:      [[b0:%\d+]] = OpLoad %bool %b0
  // CHECK-NEXT: [[m0:%\d+]] = OpLoad %int %m
  // CHECK-NEXT: [[n0:%\d+]] = OpLoad %int %n
  // CHECK-NEXT: [[s0:%\d+]] = OpSelect %int [[b0]] [[m0]] [[n0]]
  // CHECK-NEXT: OpStore %o [[s0]]
  o = select(b0, m, n);

  bool1 b1;
  bool3 b3;
  uint1 p, q, r;
  float3 x, y, z;
  // Plain assign (vector)
  // CHECK-NEXT: [[b1:%\d+]] = OpLoad %bool %b1
  // CHECK-NEXT: [[p0:%\d+]] = OpLoad %uint %p
  // CHECK-NEXT: [[q0:%\d+]] = OpLoad %uint %q
  // CHECK-NEXT: [[s1:%\d+]] = OpSelect %uint [[b1]] [[p0]] [[q0]]
  // CHECK-NEXT: OpStore %r [[s1]]
  r = select(b1, p, q);
  // CHECK-NEXT: [[b3:%\d+]] = OpLoad %v3bool %b3
  // CHECK-NEXT: [[x0:%\d+]] = OpLoad %v3float %x
  // CHECK-NEXT: [[y0:%\d+]] = OpLoad %v3float %y
  // CHECK-NEXT: [[s2:%\d+]] = OpSelect %v3float [[b3]] [[x0]] [[y0]]
  // CHECK-NEXT: OpStore %z [[s2]]
  z = select(b3, x, y);

  // Try condition with various type.
  // Note: the SPIR-V OpSelect selection argument must be the same size as the return type.
  int3 u, v, w;
  float2x3 umat, vmat, wmat;
  bool cond;
  bool3 cond3;
  float floatCond;
  int intCond;
  int3 int3Cond;

  // CHECK:      [[cond3:%\d+]] = OpLoad %v3bool %cond3
  // CHECK-NEXT:     [[u:%\d+]] = OpLoad %v3int %u
  // CHECK-NEXT:     [[v:%\d+]] = OpLoad %v3int %v
  // CHECK-NEXT:       {{%\d+}} = OpSelect %v3int [[cond3]] [[u]] [[v]]
  w = select(cond3, u, v);

  // CHECK:       [[cond:%\d+]] = OpLoad %bool %cond
  // CHECK-NEXT: [[splat:%\d+]] = OpCompositeConstruct %v3bool [[cond]] [[cond]] [[cond]]
  // CHECK-NEXT:     [[u:%\d+]] = OpLoad %v3int %u
  // CHECK-NEXT:     [[v:%\d+]] = OpLoad %v3int %v
  // CHECK-NEXT:       {{%\d+}} = OpSelect %v3int [[splat]] [[u]] [[v]]
  w = select(cond, u, v);

  // CHECK:      [[floatCond:%\d+]] = OpLoad %float %floatCond
  // CHECK-NEXT:  [[boolCond:%\d+]] = OpFOrdNotEqual %bool [[floatCond]] %float_0
  // CHECK-NEXT: [[bool3Cond:%\d+]] = OpCompositeConstruct %v3bool [[boolCond]] [[boolCond]] [[boolCond]]
  // CHECK-NEXT:         [[u:%\d+]] = OpLoad %v3int %u
  // CHECK-NEXT:         [[v:%\d+]] = OpLoad %v3int %v
  // CHECK-NEXT:           {{%\d+}} = OpSelect %v3int [[bool3Cond]] [[u]] [[v]]
  w = select(floatCond, u, v);

  // CHECK:       [[int3Cond:%\d+]] = OpLoad %v3int %int3Cond
  // CHECK-NEXT: [[bool3Cond:%\d+]] = OpINotEqual %v3bool [[int3Cond]] [[v3i0]]
  // CHECK-NEXT:         [[u:%\d+]] = OpLoad %v3int %u
  // CHECK-NEXT:         [[v:%\d+]] = OpLoad %v3int %v
  // CHECK-NEXT:           {{%\d+}} = OpSelect %v3int [[bool3Cond]] [[u]] [[v]]
  w = select(int3Cond, u, v);

  // CHECK:       [[intCond:%\d+]] = OpLoad %int %intCond
  // CHECK-NEXT: [[boolCond:%\d+]] = OpINotEqual %bool [[intCond]] %int_0
  // CHECK-NEXT:     [[umat:%\d+]] = OpLoad %mat2v3float %umat
  // CHECK-NEXT:     [[vmat:%\d+]] = OpLoad %mat2v3float %vmat
  // CHECK-NEXT:                     OpSelectionMerge %if_merge None
  // CHECK-NEXT:                     OpBranchConditional [[boolCond]] %if_true %if_false
  // CHECK-NEXT:          %if_true = OpLabel
  // CHECK-NEXT:                     OpStore %temp_var_ternary [[umat]]
  // CHECK-NEXT:                     OpBranch %if_merge
  // CHECK-NEXT:         %if_false = OpLabel
  // CHECK-NEXT:                     OpStore %temp_var_ternary [[vmat]]
  // CHECK-NEXT:                     OpBranch %if_merge
  // CHECK-NEXT:         %if_merge = OpLabel
  // CHECK-NEXT:  [[tempVar:%\d+]] = OpLoad %mat2v3float %temp_var_ternary
  // CHECK-NEXT:                     OpStore %wmat [[tempVar]]
  wmat = select(intCond, umat, vmat);

  // Make sure literal types are handled correctly in ternary ops

  // CHECK: [[b_float:%\d+]] = OpSelect %float {{%\d+}} %float_1_5 %float_2_5
  // CHECK-NEXT:    {{%\d+}} = OpConvertFToS %int [[b_float]]
  int b = select(cond, 1.5, 2.5);

  // CHECK:      [[a_int:%\d+]] = OpSelect %int {{%\d+}} %int_1 %int_0
  // CHECK-NEXT:       {{%\d+}} = OpConvertSToF %float [[a_int]]
  float a = select(cond, 1, 0);

  // CHECK:      [[c_long:%\d+]] = OpSelect %long {{%\d+}} %long_3000000000 %long_4000000000
  double c = select(cond, 3000000000, 4000000000);

  // CHECK:      [[d_int:%\d+]] = OpSelect %int {{%\d+}} %int_1 %int_0
  // CHECK-NEXT:       {{%\d+}} = OpBitcast %uint [[d_int]]
  uint d = select(cond, 1, 0);

  float2x3 e;
  float2x3 f;
  // CHECK:     [[cond:%\d+]] = OpLoad %bool %cond
  // CHECK-NEXT:   [[e:%\d+]] = OpLoad %mat2v3float %e
  // CHECK-NEXT:   [[f:%\d+]] = OpLoad %mat2v3float %f
  // CHECK-NEXT:                OpSelectionMerge %if_merge_0 None
  // CHECK-NEXT:                OpBranchConditional [[cond]] %if_true_0 %if_false_0
  // CHECK-NEXT:   %if_true_0 = OpLabel
  // CHECK-NEXT:                OpStore %temp_var_ternary_0 [[e]]
  // CHECK-NEXT:                OpBranch %if_merge_0
  // CHECK-NEXT:  %if_false_0 = OpLabel
  // CHECK-NEXT:                OpStore %temp_var_ternary_0 [[f]]
  // CHECK-NEXT:                OpBranch %if_merge_0
  // CHECK-NEXT:  %if_merge_0 = OpLabel
  // CHECK-NEXT:[[temp:%\d+]] = OpLoad %mat2v3float %temp_var_ternary_0
  // CHECK-NEXT:                OpStore %g [[temp]]
  float2x3 g = select(cond, e, f);

  // CHECK:       [[inner:%\d+]] = OpSelect %int {{%\d+}} %int_1 %int_2
  // CHECK:      [[outter:%\d+]] = OpSelect %int {{%\d+}} %int_9 [[inner]]
  // CHECK-NEXT:       {{%\d+}} = OpBitcast %uint [[outter]]
  uint h = select(cond, 9, select(cond, 1, 2));

  //CHECK:      [[i_int:%\d+]] = OpSelect %int {{%\d+}} %int_1 %int_0
  //CHECK-NEXT:       {{%\d+}} = OpINotEqual %bool [[i_int]] %int_0
  bool i = select(cond, 1, 0);

  // CHECK:     [[foo:%\d+]] = OpFunctionCall %uint %foo
  // CHECKNEXT:     {{%\d+}} = OpSelect %uint {{%\d+}} %uint_3 [[foo]]
  uint j = select(cond, 3, foo());

  // CHECK:          [[bar:%\d+]] = OpFunctionCall %float %bar
  // CHECK-NEXT: [[k_float:%\d+]] = OpSelect %float {{%\d+}} %float_4 [[bar]]
  // CHECK-NEXT:         {{%\d+}} = OpConvertFToU %uint [[k_float]]
  uint k = select(cond, 4, bar());

  zoo();

  // CHECK:       [[cond2x3:%\d+]] = OpLoad %_arr_v3bool_uint_2 %cond2x3
  // CHECK-NEXT:  [[true2x3:%\d+]] = OpLoad %mat2v3float %true2x3
  // CHECK-NEXT: [[false2x3:%\d+]] = OpLoad %mat2v3float %false2x3
  // CHECK-NEXT:       [[c0:%\d+]] = OpCompositeExtract %v3bool [[cond2x3]] 0
  // CHECK-NEXT:       [[t0:%\d+]] = OpCompositeExtract %v3float [[true2x3]] 0
  // CHECK-NEXT:       [[f0:%\d+]] = OpCompositeExtract %v3float [[false2x3]] 0
  // CHECK-NEXT:       [[r0:%\d+]] = OpSelect %v3float [[c0]] [[t0]] [[f0]]
  // CHECK-NEXT:       [[c1:%\d+]] = OpCompositeExtract %v3bool [[cond2x3]] 1
  // CHECK-NEXT:       [[t1:%\d+]] = OpCompositeExtract %v3float [[true2x3]] 1
  // CHECK-NEXT:       [[f1:%\d+]] = OpCompositeExtract %v3float [[false2x3]] 1
  // CHECK-NEXT:       [[r1:%\d+]] = OpSelect %v3float [[c1]] [[t1]] [[f1]]
  // CHECK-NEXT:   [[result:%\d+]] = OpCompositeConstruct %mat2v3float [[r0]] [[r1]]
  // CHECK-NEXT:                     OpStore %result2x3 [[result]]
  bool2x3 cond2x3;
  float2x3 true2x3, false2x3;
  float2x3 result2x3 = select(cond2x3, true2x3, false2x3);
}

//
// The literal integer type should be deduced from the function return type.
//
// CHECK:      [[result:%\d+]] = OpSelect %int {{%\d+}} %int_1 %int_2
// CHECK-NEXT:        {{%\d+}} = OpBitcast %uint [[result]]
uint zoo() {
  bool cond;
  return select(cond, 1, 2);
}

