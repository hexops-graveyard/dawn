// RUN: %dxc -T ps_6_0 -E main

// TODO:
// * operands of mixed signedness (need casting)
// * operands of bool type (need casting)

void main() {
// CHECK-LABEL: %bb_entry = OpLabel
    int a, b, c;
    uint i, j, k;

// CHECK:      [[a0:%\d+]] = OpLoad %int %a
// CHECK-NEXT: [[b0:%\d+]] = OpLoad %int %b
// CHECK-NEXT: [[c0:%\d+]] = OpBitwiseAnd %int [[a0]] [[b0]]
// CHECK-NEXT: OpStore %c [[c0]]
    c = a & b;
// CHECK-NEXT: [[i0:%\d+]] = OpLoad %uint %i
// CHECK-NEXT: [[j0:%\d+]] = OpLoad %uint %j
// CHECK-NEXT: [[k0:%\d+]] = OpBitwiseAnd %uint [[i0]] [[j0]]
// CHECK-NEXT: OpStore %k [[k0]]
    k = i & j;

// CHECK-NEXT: [[a1:%\d+]] = OpLoad %int %a
// CHECK-NEXT: [[b1:%\d+]] = OpLoad %int %b
// CHECK-NEXT: [[c1:%\d+]] = OpBitwiseOr %int [[a1]] [[b1]]
// CHECK-NEXT: OpStore %c [[c1]]
    c = a | b;
// CHECK-NEXT: [[i1:%\d+]] = OpLoad %uint %i
// CHECK-NEXT: [[j1:%\d+]] = OpLoad %uint %j
// CHECK-NEXT: [[k1:%\d+]] = OpBitwiseOr %uint [[i1]] [[j1]]
// CHECK-NEXT: OpStore %k [[k1]]
    k = i | j;

// CHECK-NEXT: [[a2:%\d+]] = OpLoad %int %a
// CHECK-NEXT: [[b2:%\d+]] = OpLoad %int %b
// CHECK-NEXT: [[c2:%\d+]] = OpBitwiseXor %int [[a2]] [[b2]]
// CHECK-NEXT: OpStore %c [[c2]]
    c = a ^ b;
// CHECK-NEXT: [[i2:%\d+]] = OpLoad %uint %i
// CHECK-NEXT: [[j2:%\d+]] = OpLoad %uint %j
// CHECK-NEXT: [[k2:%\d+]] = OpBitwiseXor %uint [[i2]] [[j2]]
// CHECK-NEXT: OpStore %k [[k2]]
    k = i ^ j;

// CHECK-NEXT: [[a5:%\d+]] = OpLoad %int %a
// CHECK-NEXT: [[b5:%\d+]] = OpNot %int [[a5]]
// CHECK-NEXT: OpStore %b [[b5]]
    b = ~a;
// CHECK-NEXT: [[i5:%\d+]] = OpLoad %uint %i
// CHECK-NEXT: [[j5:%\d+]] = OpNot %uint [[i5]]
// CHECK-NEXT: OpStore %j [[j5]]
    j = ~i;
}
