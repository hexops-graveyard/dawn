// RUN: %dxc -T vs_6_0 -E main

[[vk::constant_id(0)]]
const bool sc0 = true;

[[vk::constant_id(5)]]
static const int sc5 = 1; // error

float main() : A {
    return 1.0;
}

// CHECK: :7:18: error: specialization constant must be externally visible
