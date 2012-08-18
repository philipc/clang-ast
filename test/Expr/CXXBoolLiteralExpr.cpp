// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test1
// CHECK-NEXT:   BuiltinType bool
// CHECK-NEXT:   CXXBoolLiteralExpr true
bool test1 = true;

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test2
// CHECK-NEXT:   BuiltinType bool
// CHECK-NEXT:   CXXBoolLiteralExpr false
bool test2 = false;
