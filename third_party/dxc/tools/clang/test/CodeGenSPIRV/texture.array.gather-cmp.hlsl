// RUN: %dxc -T ps_6_0 -E main

SamplerComparisonState gSampler : register(s5);

Texture2DArray<float4> t1 : register(t1);
Texture2DArray<float2> t2 : register(t2);
Texture2DArray<float>  t3 : register(t3);
TextureCubeArray<float>t4 : register(t4);
// .GatherCmp() does not support Texture1DArray.

// CHECK: [[v2ic:%\d+]] = OpConstantComposite %v2int %int_1 %int_2
// CHECK: [[v3fc:%\d+]] = OpConstantComposite %v3float %float_1 %float_2 %float_3
// CHECK: [[v4fc:%\d+]] = OpConstantComposite %v4float %float_1_5 %float_1_5 %float_1_5 %float_1_5

// CHECK: %SparseResidencyStruct = OpTypeStruct %uint %v4float

float4 main(float3 location: A, float comparator: B, int2 offset: C) : SV_Target {
// CHECK:              [[t2:%\d+]] = OpLoad %type_2d_image_array %t1
// CHECK-NEXT:   [[gSampler:%\d+]] = OpLoad %type_sampler %gSampler
// CHECK-NEXT:        [[loc:%\d+]] = OpLoad %v3float %location
// CHECK-NEXT: [[comparator:%\d+]] = OpLoad %float %comparator
// CHECK-NEXT: [[sampledImg:%\d+]] = OpSampledImage %type_sampled_image [[t2]] [[gSampler]]
// CHECK-NEXT:            {{%\d+}} = OpImageDrefGather %v4float [[sampledImg]] [[loc]] [[comparator]] ConstOffset [[v2ic]]
    float4 val1 = t1.GatherCmp(gSampler, location, comparator, int2(1, 2));

// CHECK:              [[t2:%\d+]] = OpLoad %type_2d_image_array %t2
// CHECK-NEXT:   [[gSampler:%\d+]] = OpLoad %type_sampler %gSampler
// CHECK-NEXT: [[comparator:%\d+]] = OpLoad %float %comparator
// CHECK-NEXT: [[sampledImg:%\d+]] = OpSampledImage %type_sampled_image [[t2]] [[gSampler]]
// CHECK-NEXT:            {{%\d+}} = OpImageDrefGather %v4float [[sampledImg]] [[v3fc]] [[comparator]]
    float4 val2 = t2.GatherCmp(gSampler, float3(1, 2, 3), comparator);

// CHECK:              [[t3:%\d+]] = OpLoad %type_2d_image_array %t3
// CHECK-NEXT:   [[gSampler:%\d+]] = OpLoad %type_sampler %gSampler
// CHECK-NEXT:        [[loc:%\d+]] = OpLoad %v3float %location
// CHECK-NEXT: [[comparator:%\d+]] = OpLoad %float %comparator
// CHECK-NEXT:     [[offset:%\d+]] = OpLoad %v2int %offset
// CHECK-NEXT: [[sampledImg:%\d+]] = OpSampledImage %type_sampled_image [[t3]] [[gSampler]]
// CHECK-NEXT:            {{%\d+}} = OpImageDrefGather %v4float [[sampledImg]] [[loc]] [[comparator]] Offset [[offset]]
    float4 val3 = t3.GatherCmp(gSampler, location, comparator, offset);

    uint status;

// CHECK:                [[t3:%\d+]] = OpLoad %type_2d_image_array %t3
// CHECK-NEXT:     [[gSampler:%\d+]] = OpLoad %type_sampler %gSampler
// CHECK-NEXT:          [[loc:%\d+]] = OpLoad %v3float %location
// CHECK-NEXT:   [[comparator:%\d+]] = OpLoad %float %comparator
// CHECK-NEXT:       [[offset:%\d+]] = OpLoad %v2int %offset
// CHECK-NEXT:   [[sampledImg:%\d+]] = OpSampledImage %type_sampled_image [[t3]] [[gSampler]]
// CHECK-NEXT: [[structResult:%\d+]] = OpImageSparseDrefGather %SparseResidencyStruct [[sampledImg]] [[loc]] [[comparator]] Offset [[offset]]
// CHECK-NEXT:       [[status:%\d+]] = OpCompositeExtract %uint [[structResult]] 0
// CHECK-NEXT:                         OpStore %status [[status]]
// CHECK-NEXT:       [[result:%\d+]] = OpCompositeExtract %v4float [[structResult]] 1
// CHECK-NEXT:                         OpStore %val4 [[result]]
    float4 val4 = t3.GatherCmp(gSampler, location, comparator, offset, status);

// CHECK:                [[t4:%\d+]] = OpLoad %type_cube_image_array %t4
// CHECK-NEXT:     [[gSampler:%\d+]] = OpLoad %type_sampler %gSampler
// CHECK-NEXT:   [[comparator:%\d+]] = OpLoad %float %comparator
// CHECK-NEXT:   [[sampledImg:%\d+]] = OpSampledImage %type_sampled_image_0 [[t4]] [[gSampler]]
// CHECK-NEXT: [[structResult:%\d+]] = OpImageSparseDrefGather %SparseResidencyStruct [[sampledImg]] [[v4fc]] [[comparator]] None
// CHECK-NEXT:       [[status:%\d+]] = OpCompositeExtract %uint [[structResult]] 0
// CHECK-NEXT:                         OpStore %status [[status]]
// CHECK-NEXT:       [[result:%\d+]] = OpCompositeExtract %v4float [[structResult]] 1
// CHECK-NEXT:                         OpStore %val5 [[result]]
    float4 val5 = t4.GatherCmp(gSampler, /*location*/float4(1.5, 1.5, 1.5, 1.5), comparator, status);

    return 1.0;
}
