// RUN: ast -f test -- -Wno-warn-unused "%s" 2>&1 | FileCheck %s

struct A {
  operator int();
};

void test1() {
  A a;
  int i;

  // CHECK:     BinaryOperator
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr UserDefinedConversion
  // CHECK-NEXT:         CXXMemberCallExpr
  // CHECK-NEXT:           MemberExpr
  // CHECK-NEXT:             DeclarationName operator int
  // CHECK-NEXT:             DeclRefExpr
  // CHECK-NEXT:               DeclarationName a
  i = a;
}

enum e {
  // CHECK-NEXT: EnumConstantDecl
  // CHECK-NEXT:   DeclarationName test2
  // CHECK-NEXT:   ImplicitCastExpr IntegralCast
  // CHECK-NEXT:     CharacterLiteral 97
  test2 = 'a'
};
