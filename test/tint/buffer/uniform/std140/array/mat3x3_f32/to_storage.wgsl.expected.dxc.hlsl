cbuffer cbuffer_u : register(b0, space0) {
  uint4 u[12];
};
RWByteAddressBuffer s : register(u1, space0);

void s_store_1(uint offset, float3x3 value) {
  s.Store3((offset + 0u), asuint(value[0u]));
  s.Store3((offset + 16u), asuint(value[1u]));
  s.Store3((offset + 32u), asuint(value[2u]));
}

void s_store(uint offset, float3x3 value[4]) {
  float3x3 array_1[4] = value;
  {
    for(uint i = 0u; (i < 4u); i = (i + 1u)) {
      s_store_1((offset + (i * 48u)), array_1[i]);
    }
  }
}

float3x3 u_load_1(uint offset) {
  const uint scalar_offset = ((offset + 0u)) / 4;
  const uint scalar_offset_1 = ((offset + 16u)) / 4;
  const uint scalar_offset_2 = ((offset + 32u)) / 4;
  return float3x3(asfloat(u[scalar_offset / 4].xyz), asfloat(u[scalar_offset_1 / 4].xyz), asfloat(u[scalar_offset_2 / 4].xyz));
}

typedef float3x3 u_load_ret[4];
u_load_ret u_load(uint offset) {
  float3x3 arr[4] = (float3x3[4])0;
  {
    for(uint i_1 = 0u; (i_1 < 4u); i_1 = (i_1 + 1u)) {
      arr[i_1] = u_load_1((offset + (i_1 * 48u)));
    }
  }
  return arr;
}

[numthreads(1, 1, 1)]
void f() {
  s_store(0u, u_load(0u));
  s_store_1(48u, u_load_1(96u));
  s.Store3(48u, asuint(asfloat(u[1].xyz).zxy));
  s.Store(48u, asuint(asfloat(u[1].x)));
  return;
}
