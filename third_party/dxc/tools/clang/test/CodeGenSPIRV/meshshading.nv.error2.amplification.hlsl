// RUN: %dxc -T as_6_5 -E main

struct MeshPayload {
    float4 pos;
};

#define NUM_THREADS 128

[numthreads(NUM_THREADS, 1, 1)]
void main()
{
    MeshPayload pld;
    pld.pos = float4(3.0,4.0,5.0,6.0);

// CHECK:  16:37: error: expected groupshared object as argument to DispatchMesh()
    DispatchMesh(NUM_THREADS, 1, 1, pld);
}
