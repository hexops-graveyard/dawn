// RUN: %clang_cc1 -fsyntax-only -Wno-unused-value -ffreestanding -verify -HV 2021 %s

// This test checks that when we use undefined overloaded operator
// dxcompiler generates error and no crashes are observed.

struct S1 {
    float a;

    float operator+(float x) {
        return a + x;
    }
};

struct S2 {
    S1 s1;
};

void main(float4 pos: SV_Position) {
    S1 s1;
    S2 s2;
    pos.x = s2.s1 + 0.1;
    pos.x = s2.s1 + s1; // expected-error {{invalid operands to binary expression ('S1' and 'S1')}}
}
