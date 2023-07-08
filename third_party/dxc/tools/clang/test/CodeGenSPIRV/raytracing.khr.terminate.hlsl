// RUN: %dxc -T lib_6_3 -fspv-target-env=vulkan1.2
// CHECK:  OpCapability RayTracingKHR
// CHECK:  OpExtension "SPV_KHR_ray_tracing"

// CHECK:  OpDecorate [[l:%\d+]] BuiltIn HitKindNV

// CHECK:  OpTypePointer IncomingRayPayloadNV %Payload
struct Payload
{
  float4 color;
};
// CHECK:  OpTypePointer HitAttributeNV %Attribute
struct Attribute
{
  float2 bary;
};

[shader("anyhit")]
void MyAHitMain(inout Payload MyPayload, in Attribute MyAttr) {

// CHECK:  OpLoad %uint [[l]]
  uint _16 = HitKind();

// CHECK: %if_true = OpLabel
  if (_16 == 1U) {
// CHECK: OpIgnoreIntersectionKHR
    IgnoreHit();
// CHECK-NOT: OpLoad %uint %_16
// CHECK-NOT: OpStore
    uint a = _16;
// CHECK-NEXT: %if_false = OpLabel
  } else {
// CHECK: OpTerminateRayKHR
    AcceptHitAndEndSearch();
// CHECK-NOT: OpLoad %uint %_16
// CHECK-NOT: OpStore
    uint b = _16;
  }
// CHECK-NEXT: %if_merge = OpLabel
// CHECK-NEXT: OpReturn
// CHECK-NEXT: OpFunctionEnd
}


[shader("anyhit")]
void MyAHitMain2(inout Payload MyPayload, in Attribute MyAttr) {
// CHECK: OpTerminateRayKHR
    AcceptHitAndEndSearch();
// CHECK-NOT: OpAccessChain
// CHECK-NOT: OpStore
    MyPayload.color = 0.xxxx;
// CHECK-NEXT: OpFunctionEnd
}
