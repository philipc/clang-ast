// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: ParmVarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType int
// CHECK: ParmVarDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 0
void f(int test1, int test2 = 0);
