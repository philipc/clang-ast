// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType double
// CHECK-NEXT:   FloatingLiteral 1.000000e+00
double test1 = 1.0;
