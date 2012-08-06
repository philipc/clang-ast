// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  __label__ l;
  l: goto l;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       LabelDecl l
// CHECK-NEXT:     LabelStmt l
// CHECK-NEXT:       GotoStmt
