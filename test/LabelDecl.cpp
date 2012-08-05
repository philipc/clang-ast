// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  __label__ l;
  l: goto l;
};

// CHECK: Function test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       Label l
// CHECK-NEXT:     LabelStmt
// CHECK-NEXT:       Label l
// CHECK-NEXT:       GotoStmt
