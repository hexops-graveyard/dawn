// RUN: %dxc -T cs_6_0 -HV 2018 -E main

// According to the SPIR-V spec (2.14. Relaxed Precision):
// The RelaxedPrecision decoration can be applied to:
// The Result <id> of an instruction that operates on numerical types, meaning
// the instruction is to operate at relaxed precision. The instruction's
// operands may also be truncated to the relaxed precision.
//
// In this example, (a > 0.0) comparison is operating on floats with relaxed
// precision, and should therefore have the decoration. However, the "any"
// intrinsic function is operating on a vector of booleans, and it should not
// be decorated.

// CHECK:     OpDecorate %a RelaxedPrecision
// CHECK:     OpDecorate %b RelaxedPrecision
// CHECK:     OpDecorate [[a:%\d+]] RelaxedPrecision
// CHECK:     OpDecorate [[compare_op:%\d+]] RelaxedPrecision
// CHECK:     OpDecorate [[b:%\d+]] RelaxedPrecision
// CHECK:     OpDecorate [[compare_op_2:%\d+]] RelaxedPrecision
//
// We should NOT have a decoration for the 'any' operation.
// We should NOT have a decoration for the '||' operation.
//
// CHECK-NOT: OpDecorate {{%\d+}} RelaxedPrecision

// CHECK:            [[a]] = OpLoad %float %a
// CHECK:   [[compare_op]] = OpFOrdGreaterThan %bool [[a]] %float_0
// CHECK:            [[b]] = OpLoad %v2float %b
// CHECK: [[compare_op_2]] = OpFOrdGreaterThan %v2bool [[b]] {{%\d+}}
// CHECK:  [[any_op:%\d+]] = OpAny %bool %26
// CHECK:   [[or_op:%\d+]] = OpLogicalOr %bool

RWBuffer<float2> Buf;

[numthreads(1, 1, 1)]
void main() {
  // Scalar
  min16float a;

  // Vector
  min16float2 b;

  bool x = (a > 0.0) || any(b > 0.0);
}
