// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   ComplexType
// CHECK-NEXT:     BuiltinType double
// CHECK-NEXT:   ImaginaryLiteral
// CHECK-NEXT:     FloatingLiteral 1.000000e+00
double _Complex test1 = 1.0i;
