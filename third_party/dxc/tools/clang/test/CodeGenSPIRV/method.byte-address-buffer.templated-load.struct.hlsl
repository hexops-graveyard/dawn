// RUN: %dxc -T cs_6_2 -E main -enable-16bit-types -fvk-use-dx-layout

ByteAddressBuffer buf;
RWByteAddressBuffer buf2;

struct S {
  float16_t3 a[3];
  float b;
  double c;
  float16_t d;
};

[numthreads(64, 1, 1)]
void main(uint3 tid : SV_DispatchThreadId) {
  S sArr[2] = buf.Load<S[2]>(tid.x);
}

// Here is the DXIL output with the load offsets:
//
// define void @main() {
//   COMMENT: Load at address tid.x (offset = 0):
//   %RawBufferLoad36 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %1, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 6 (offset = 6 bytes):
//   %5 = add i32 %1, 6
//   %RawBufferLoad35 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %5, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 12 (offset = 12 bytes):
//   %9 = add i32 %1, 12
//   %RawBufferLoad = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %9, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 20 (offset = 20 bytes):
//   %13 = add i32 %1, 20
//   %RawBufferLoad45 = call %dx.types.ResRet.f32 @dx.op.rawBufferLoad.f32(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %13, i32 undef, i8 1, i32 4)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 24 (offset = 24 bytes):
//   %15 = add i32 %1, 24
//   %16 = call %dx.types.ResRet.i32 @dx.op.rawBufferLoad.i32(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %15, i32 undef, i8 3, i32 8)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 32 (offset = 32 bytes):
//   %20 = add i32 %1, 32
//   %RawBufferLoad43 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %20, i32 undef, i8 1, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: The load of the first struct in sArr has finished.
//   COMMENT: Padding must be applied until we reach the struct alignment.
//   COMMENT: The second struct in sArr starts at offset 40.
//   COMMENT: Load at address tid.x + 40 (offset = 40 bytes):
//   %22 = add i32 %1, 40
//   %RawBufferLoad39 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %22, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 46 (offset = 46 bytes):
//   %26 = add i32 %1, 46
//   %RawBufferLoad38 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %26, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 52 (offset = 52 bytes):
//   %30 = add i32 %1, 52
//   %RawBufferLoad37 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %30, i32 undef, i8 7, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 60 (offset = 60 bytes):
//   %34 = add i32 %1, 60
//   %RawBufferLoad42 = call %dx.types.ResRet.f32 @dx.op.rawBufferLoad.f32(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %34, i32 undef, i8 1, i32 4)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 64 (offset = 64 bytes):
//   %36 = add i32 %1, 64
//   %37 = call %dx.types.ResRet.i32 @dx.op.rawBufferLoad.i32(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %36, i32 undef, i8 3, i32 8)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
//   COMMENT: Load at address tid.x + 72 (offset = 72 bytes):
//   %41 = add i32 %1, 72
//   %RawBufferLoad40 = call %dx.types.ResRet.f16 @dx.op.rawBufferLoad.f16(i32 139, %dx.types.Handle %buf_texture_rawbuf, i32 %41, i32 undef, i8 1, i32 2)  ; RawBufferLoad(srv,index,elementOffset,mask,alignment)
//   ...
// }


// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_0:%\d+]]
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_0:%\d+]]
// CHECK: [[index_1:%\d+]] = OpIAdd %uint [[index_0]] %uint_1
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_1]]
// CHECK:   [[aVec0:%\d+]] = OpCompositeConstruct %v3half
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_1]]
// CHECK: [[index_2:%\d+]] = OpIAdd %uint [[index_1]] %uint_1
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_2]]
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_2]]
// CHECK: [[index_3:%\d+]] = OpIAdd %uint [[index_2]] %uint_1
// CHECK:   [[aVec1:%\d+]] = OpCompositeConstruct %v3half
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_3]]
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_3]]
// CHECK: [[index_4:%\d+]] = OpIAdd %uint [[index_3]] %uint_1
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_4]]
// CHECK:   [[aVec2:%\d+]] = OpCompositeConstruct %v3half
// CHECK:       [[a:%\d+]] = OpCompositeConstruct %_arr_v3half_uint_3 [[aVec0]] [[aVec1]] [[aVec2]]
//
// COMMENT: Going to start loading 'b'. Must start at byte offset 20
// COMMENT: 20 byte offset is equivalent to 5 words offset (32-bit words).
// COMMENT: 'b' is 32-bit wide, so it will consume 1 word.
//
// CHECK: [[index_5:%\d+]] = OpIAdd %uint [[index_0]] %uint_5
// CHECK:     [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_5]]
//
// COMMENT: Going to start loading 'c'. Must start at byte offset 24
// COMMENT: 24 byte offset is equivalent to 6 words offset (32-bit words).
// COMMENT: 'c' is 64-bit wide, so it will consume 2 words.
//
// CHECK: [[index_6:%\d+]] = OpIAdd %uint [[index_0]] %uint_6
// CHECK: [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_6]]
// CHECK: [[index_7:%\d+]] = OpIAdd %uint [[index_6]] %uint_1
// CHECK: [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_7]]
//
// COMMENT: Going to start loading 'd'. Must start at byte offset 32.
// COMMENT: 32 byte offset is equivalent to 8 words offset (32-bit words).
// COMMENT: 'd' is 16-bit wide, so it will consume half of one word.
//
// CHECK: [[index_8:%\d+]] = OpIAdd %uint [[index_0]] %uint_8
// CHECK: [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_8]]
// CHECK: [[index_10:%\d+]] = OpIAdd %uint [[index_0]] %uint_10
// CHECK: [[s_0:%\d+]] = OpCompositeConstruct %S
//
// COMMENT: Going to start loading the second struct in sArr.
// COMMENT: The structure is 8-byte aligned (due to the existence of 'double')
// COMMENT: The last struct in the array ended at offset 34.
// COMMENT: We need to add padding up to offset 40 (to be 8-byte aligned).
// COMMENT: 40 byte offset is equivalent to 10 words offset (32-bit words).
//
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_10]]
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_10]]
// CHECK: [[index_11:%\d+]] = OpIAdd %uint [[index_10]] %uint_1
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_11]]
// CHECK:    [[aVec0:%\d+]] = OpCompositeConstruct %v3half
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_11]]
// CHECK: [[index_12:%\d+]] = OpIAdd %uint [[index_11]] %uint_1
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_12]]
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_12]]
// CHECK: [[index_13:%\d+]] = OpIAdd %uint [[index_12]] %uint_1
// CHECK:    [[aVec1:%\d+]] = OpCompositeConstruct %v3half
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_13]]
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_13]]
// CHECK: [[index_14:%\d+]] = OpIAdd %uint [[index_13]] %uint_1
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_14]]
// CHECK:    [[aVec2:%\d+]] = OpCompositeConstruct %v3half
// CHECK:        [[a:%\d+]] = OpCompositeConstruct %_arr_v3half_uint_3 [[aVec0]] [[aVec1]] [[aVec2]]
//
// COMMENT: Similar to the load of the first struct, member 'b' is at offset 20
// COMMENT: from the beginning of the struct. The second struct starts at offset 40
// COMMENT: Therefore the second struct's 'b' starts at offset 60.
// COMMENT: 60 byte offset is equivalent to 15 words offset (32-bit words).
//
// CHECK: [[index_15:%\d+]] = OpIAdd %uint [[index_10]] %uint_5
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_15]]
//
// COMMENT: member 'c' must start at offset 40 + 24 = 64
// COMMENT: 64 byte offset is equivalent to 16 words offset (32-bit words).
// COMMENT: 'c' is 64-bit wide, so it will consume 2 words.
//
// CHECK: [[index_16:%\d+]] = OpIAdd %uint [[index_10]] %uint_6
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_16]]
// CHECK: [[index_17:%\d+]] = OpIAdd %uint [[index_16]] %uint_1
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_17]]
//
// COMMENT: member 'd' must start at offset 40 + 32 = 72
// COMMENT: 72 byte offset is equivalent to 18 words offset (32-bit words).
// COMMENT: 'c' is 16-bit wide, so it will consume half of one word.
//
// CHECK: [[index_18:%\d+]] = OpIAdd %uint [[index_10]] %uint_8
// CHECK:      [[ptr:%\d+]] = OpAccessChain %_ptr_Uniform_uint %buf %uint_0 [[index_18]]
//
// COMMENT: Construct sArr[2]
//
// CHECK:                     OpCompositeConstruct %S
// CHECK:                     OpCompositeConstruct %_arr_S_uint_2
// CHECK:                     OpStore %sArr {{%\d+}}

