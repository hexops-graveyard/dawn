// RUN: %clang_cc1 -fsyntax-only -ffreestanding -HV 2021 -verify %s
RWStructuredBuffer<float> Output;

// expected-note@+1 {{candidate template ignored: deduced conflicting types for parameter 'T' ('float' vs. 'literal float')}}
template <typename T> T Add(T input, T input2) {
  return input + input2;
}

void main() {
  // expected-error@+1 {{no matching function for call to 'Add'}}
  Output[0] = Add(Output[0], 1.0)
}
