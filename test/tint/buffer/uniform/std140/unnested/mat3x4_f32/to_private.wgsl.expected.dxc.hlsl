cbuffer cbuffer_u : register(b0, space0) {
  uint4 u[3];
};
static float3x4 p = float3x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

float3x4 u_load(uint offset) {
  const uint scalar_offset = ((offset + 0u)) / 4;
  const uint scalar_offset_1 = ((offset + 16u)) / 4;
  const uint scalar_offset_2 = ((offset + 32u)) / 4;
  return float3x4(asfloat(u[scalar_offset / 4]), asfloat(u[scalar_offset_1 / 4]), asfloat(u[scalar_offset_2 / 4]));
}

[numthreads(1, 1, 1)]
void f() {
  p = u_load(0u);
  p[1] = asfloat(u[0]);
  p[1] = asfloat(u[0]).ywxz;
  p[0][1] = asfloat(u[1].x);
  return;
}
