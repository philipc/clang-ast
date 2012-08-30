// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: EnumConstantDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT: EnumConstantDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   ImplicitCastExpr
// CHECK-NEXT:     IntegerLiteral 0
// CHECK-NEXT: EnumConstantDecl
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   ImplicitCastExpr
// CHECK-NEXT:     DeclRefExpr
// CHECK-NEXT:       DeclarationName test1
enum A {
  test1,
  test2 = 0,
  test3 = test1
};
