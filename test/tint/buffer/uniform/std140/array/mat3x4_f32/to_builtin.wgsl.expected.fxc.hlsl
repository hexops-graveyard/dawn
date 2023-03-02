cbuffer cbuffer_u : register(b0, space0) {
  uint4 u[12];
};

float3x4 u_load(uint offset) {
  const uint scalar_offset = ((offset + 0u)) / 4;
  const uint scalar_offset_1 = ((offset + 16u)) / 4;
  const uint scalar_offset_2 = ((offset + 32u)) / 4;
  return float3x4(asfloat(u[scalar_offset / 4]), asfloat(u[scalar_offset_1 / 4]), asfloat(u[scalar_offset_2 / 4]));
}

[numthreads(1, 1, 1)]
void f() {
  const float4x3 t = transpose(u_load(96u));
  const float l = length(asfloat(u[1]).ywxz);
  const float a = abs(asfloat(u[1]).ywxz.x);
  return;
}
