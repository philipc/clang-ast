// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 1
int test1 = 1;

// FIXME: test signed vs unsigned integer literals.
// Don't know how to do this, because the - is treated as a unary operator.
