// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  do
    ;
  while (true);
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     DoStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
