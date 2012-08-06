// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  int i, j;
  int k;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl i
// CHECK-NEXT:         Builtin int
// CHECK-NEXT:       VarDecl j
// CHECK-NEXT:         Builtin int
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl k
// CHECK-NEXT:         Builtin int
