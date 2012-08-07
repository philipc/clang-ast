// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  while (true)
    ;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     WhileStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
// CHECK-NEXT:       NullStmt
