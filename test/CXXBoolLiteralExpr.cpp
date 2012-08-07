// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl test1
// CHECK-NEXT:   Builtin bool
// CHECK-NEXT:   CXXBoolLiteralExpr true
bool test1 = true;

// CHECK: VarDecl test2
// CHECK-NEXT:   Builtin bool
// CHECK-NEXT:   CXXBoolLiteralExpr false
bool test2 = false;
