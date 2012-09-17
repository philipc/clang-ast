// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

struct A {
  virtual void f();
};

struct B : A {
};

void test1() {
  const char *p;
  A *a;

  // CHECK:     CStyleCastExpr NoOp
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       ImplicitCastExpr IntegralCast
  // CHECK-NEXT:         CharacterLiteral 97
  (int)'a';

  // CHECK-NEXT:     CXXStaticCastExpr NoOp
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       ImplicitCastExpr IntegralCast
  // CHECK-NEXT:         CharacterLiteral 97
  static_cast<int>('a');

  // CHECK-NEXT:     CXXConstCastExpr NoOp
  // CHECK-NEXT:       PointerType
  // CHECK-NEXT:         BuiltinType char
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName p
  const_cast<char *>(p);

  // CHECK-NEXT:     CXXReinterpretCastExpr PointerToIntegral
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName p
  reinterpret_cast<int>(p);

  // CHECK-NEXT:     CXXDynamicCastExpr Dynamic
  // CHECK-NEXT:       PointerType
  // CHECK-NEXT:         RecordType B
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName a
  dynamic_cast<B *>(a);

  // CHECK-NEXT:     CXXFunctionalCastExpr NoOp
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       ImplicitCastExpr IntegralCast
  // CHECK-NEXT:         CharacterLiteral 97
  int('a');
}
