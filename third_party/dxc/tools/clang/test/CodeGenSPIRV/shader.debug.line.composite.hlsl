// RUN: %dxc -T ps_6_0 -E main -fspv-debug=vulkan

// CHECK:      [[file:%\d+]] = OpString
// CHECK:      [[src:%\d+]] = OpExtInst %void %2 DebugSource [[file]]

struct int4_bool_float3 {
  int4 a;
  bool b;
  float3 c;
};

int4_bool_float3 test_struct() {
  int4_bool_float3 x;
  return x;
}

cbuffer CONSTANTS {
  int4_bool_float3 y;
};

RWTexture2D<int3> z;

struct S {
  int a;
  // TODO(greg-lunarg): void inc() { a++; }
};

S getS() {
  S a;
  return a;
}

struct init {
  int first;
  float second;
};

// Note that preprocessor prepends a "#line 1 ..." line to the whole file,
// the compliation sees line numbers incremented by 1.

void main() {
  S foo;

  init bar;

  int4 a = {
      float2(1, 0),
// CHECK: DebugLine [[src]] %uint_50 %uint_50 %uint_7 %uint_19
// CHECK: OpFunctionCall %int4_bool_float3_0 %test_struct
      test_struct().c.zx
// CHECK:      OpCompositeExtract %float {{%\d+}} 0
// CHECK-NEXT: OpCompositeExtract %float {{%\d+}} 1
// CHECK-NEXT: DebugLine [[src]] %uint_46 %uint_46 %uint_12 %uint_12
// CHECK-NEXT: OpConvertFToS %int
// CHECK-NEXT: OpConvertFToS %int
// CHECK:      OpCompositeConstruct %v4int
  };

// CHECK:                        OpFDiv %float {{%\d+}} %float_2
// CHECK-NEXT:                   DebugLine [[src]] %uint_64 %uint_64 %uint_16 %uint_57
// CHECK-NEXT:  [[first:%\d+]] = OpCompositeConstruct %v2float {{%\d+}} {{%\d+}}
// CHECK-NEXT: [[second:%\d+]] = OpCompositeConstruct %v2float {{%\d+}} {{%\d+}}
// CHECK-NEXT:        {{%\d+}} = OpCompositeConstruct %mat2v2float [[first]] [[second]]
  float2x2 b = float2x2(a.x, b._m00, 2 + a.y, b._m11 / 2);

// CHECK:                   DebugLine [[src]] %uint_69 %uint_69 %uint_12 %uint_14
// CHECK-NEXT: [[y:%\d+]] = OpAccessChain %_ptr_Uniform_int4_bool_float3 %CONSTANTS %int_0
// CHECK-NEXT:   {{%\d+}} = OpAccessChain %_ptr_Uniform_v4int [[y]] %int_0
  int4 c = y.a;

// CHECK:                   DebugLine [[src]] %uint_76 %uint_76 %uint_3 %uint_3
// CHECK-NEXT: [[z:%\d+]] = OpLoad %type_2d_image %z
// CHECK-NEXT: [[z:%\d+]] = OpImageRead %v4int [[z]] {{%\d+}} None
// CHECK-NEXT: [[z:%\d+]] = OpVectorShuffle %v3int [[z]] [[z]] 0 1 2
// CHECK:        {{%\d+}} = OpCompositeInsert %v3int %int_16 [[z]] 0
  z[uint2(2, 3)].x = 16;

// CHECK:      DebugLine [[src]] %uint_82 %uint_82 %uint_3 %uint_4
// CHECK-NEXT: OpLoad %mat2v2float %b
// CHECK:      DebugLine [[src]] %uint_82 %uint_82 %uint_3 %uint_4
// CHECK-NEXT: OpFSub %v2float
  b--;

  int2x2 d;
// CHECK:      DebugLine [[src]] %uint_91 %uint_91 %uint_8 %uint_8
// CHECK-NEXT: OpLoad %mat2v2float %b
// CHECK-NEXT: DebugLine [[src]] %uint_91 %uint_91 %uint_3 %uint_12
// CHECK-NEXT: OpCompositeExtract %v2float
// CHECK:      OpCompositeConstruct %_arr_v2int_uint_2
// CHECK-NEXT: OpStore %d
  modf(b, d);

// CHECK-TODO:      DebugLine [[src]] %uint_95 %uint_95 %uint_3 %uint_11
// CHECK-NEXT-TODO: OpFunctionCall %void %S_inc %foo
// TODO(greg-lunarg):  foo.inc();

// CHECK-TODO:      DebugLine [[src]] %uint_99 %uint_99 %uint_3 %uint_14
// CHECK-NEXT-TODO: OpFunctionCall %void %S_inc %temp_var_S
// TODO(greg-lunarg):  getS().inc();

// CHECK:      DebugLine [[src]] %uint_105 %uint_105 %uint_19 %uint_19
// CHECK-NEXT: OpLoad %init %bar
// CHECK:      DebugLine [[src]] %uint_105 %uint_105 %uint_12 %uint_12
// CHECK-NEXT: OpConvertFToS %int
  int4 e = {1, 2, bar};

// CHECK:      DebugLine [[src]] %uint_111 %uint_111 %uint_7 %uint_25
// CHECK-NEXT: OpCompositeConstruct %v2float %float_1 %float_2
// CHECK-NEXT: DebugLine [[src]] %uint_111 %uint_111 %uint_22 %uint_22
// CHECK-NEXT: OpCompositeExtract %int
  b = float2x2(1, 2, bar);
// CHECK:      DebugLine [[src]] %uint_111 %uint_111 %uint_3 %uint_25
// CHECK-NEXT: OpStore %b

// TODO(jaebaek): Update InitListHandler to properly emit debug info.
  b = float2x2(c);
  c = int4(b);
}
