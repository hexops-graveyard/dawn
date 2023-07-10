// RUN: %dxc -T ms_6_5 -E main

// CHECK: 14:6: error: MS entry point must have the outputtopology attribute

struct MeshPerVertex {
    float4 position : SV_Position;
};

#define MAX_VERT 64
#define MAX_PRIM 81
#define NUM_THREADS 128

[numthreads(NUM_THREADS, 1, 1)]
void main(
        out vertices MeshPerVertex verts[MAX_VERT],
        out indices uint3 primitiveInd[MAX_PRIM],
        in uint tig : SV_GroupIndex)
{
}
