// RUN: %dxc -T ps_6_0 -E main -O2 -Oconfig=--loop-unroll

void main() {}

// CHECK: -Oconfig should not be used together with -O
