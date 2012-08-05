// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  l: goto l;
};

// CHECK: Function test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     LabelStmt l
// CHECK-NEXT:       GotoStmt
