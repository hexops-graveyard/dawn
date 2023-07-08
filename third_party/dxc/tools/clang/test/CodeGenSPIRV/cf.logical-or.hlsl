// RUN: %dxc -T ps_6_0 -HV 2018 -E main

// TODO: write to global variable
bool fn() { return true; }

void main() {
// CHECK-LABEL: %bb_entry = OpLabel

    // Use in control flow

    bool a, b;
    int val = 0;
// CHECK:      [[a0:%\d+]] = OpLoad %bool %a
// CHECK-NEXT: [[b0:%\d+]] = OpLoad %bool %b
// CHECK-NEXT: [[or0:%\d+]] = OpLogicalOr %bool [[a0]] [[b0]]
// CHECK-NEXT: OpSelectionMerge %if_merge None
// CHECK-NEXT: OpBranchConditional [[or0]] %if_true %if_merge
    if (a || b) val++;

    // Operand with side effects

// CHECK-LABEL: %if_merge = OpLabel
// CHECK-NEXT: [[fn0:%\d+]] = OpFunctionCall %bool %fn
// CHECK-NEXT: [[fn1:%\d+]] = OpFunctionCall %bool %fn
// CHECK-NEXT: [[or1:%\d+]] = OpLogicalOr %bool [[fn0]] [[fn1]]
// CHECK-NEXT: OpSelectionMerge %if_merge_0 None
// CHECK-NEXT: OpBranchConditional [[or1]] %if_true_0 %if_merge_0
    if (fn() || fn()) val++;
// CHECK-LABEL: %if_merge_0 = OpLabel
// CHECK-NEXT: [[a1:%\d+]] = OpLoad %bool %a
// CHECK-NEXT: [[fn2:%\d+]] = OpFunctionCall %bool %fn
// CHECK-NEXT: [[or2:%\d+]] = OpLogicalOr %bool [[a1]] [[fn2]]
// CHECK-NEXT: OpSelectionMerge %if_merge_1 None
// CHECK-NEXT: OpBranchConditional [[or2]] %if_true_1 %if_merge_1
    if (a || fn()) val++;
// CHECK-LABEL: %if_merge_1 = OpLabel
// CHECK-NEXT: [[fn3:%\d+]] = OpFunctionCall %bool %fn
// CHECK-NEXT: [[b1:%\d+]] = OpLoad %bool %b
// CHECK-NEXT: [[or3:%\d+]] = OpLogicalOr %bool [[fn3]] [[b1]]
// CHECK-NEXT: OpSelectionMerge %if_merge_2 None
// CHECK-NEXT: OpBranchConditional [[or3]] %if_true_2 %if_merge_2
    if (fn() || b) val++;
}
// CHECK: OpFunctionEnd
