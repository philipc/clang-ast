// RUN: ast -f test -- -Wno-warn-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         Identifier i
  // CHECK-NEXT:         BuiltinType int
  // CHECK-NEXT:         IntegerLiteral 0
  int i = 0;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         Identifier p
  // CHECK-NEXT:         PointerType
  // CHECK-NEXT:           BuiltinType int
  // CHECK-NEXT:         ImplicitCastExpr
  // CHECK-NEXT:           IntegerLiteral 0
  int *p = 0;

  // CHECK-NEXT:     UnaryOperator postfix ++
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  i++;

  // CHECK-NEXT:     UnaryOperator prefix ++
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  ++i;

  // CHECK-NEXT:     UnaryOperator postfix --
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  i--;

  // CHECK-NEXT:     UnaryOperator prefix --
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  --i;

  // CHECK-NEXT:     UnaryOperator &
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  &i;

  // CHECK-NEXT:     UnaryOperator *
  // CHECK-NEXT:       ImplicitCastExpr
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName p
  *p;

  // CHECK-NEXT:     UnaryOperator +
  // CHECK-NEXT:       IntegerLiteral 1
  +1;

  // CHECK-NEXT:     UnaryOperator -
  // CHECK-NEXT:       IntegerLiteral 1
  -1;

  // CHECK-NEXT:     UnaryOperator ~
  // CHECK-NEXT:       IntegerLiteral 0
  ~0;

  // CHECK-NEXT:     UnaryOperator !
  // CHECK-NEXT:       CXXBoolLiteralExpr false
  !false;

  // CHECK-NEXT:     UnaryOperator __real
  // CHECK-NEXT:       IntegerLiteral 0
  __real__ 0;

  // CHECK-NEXT:     UnaryOperator __imag
  // CHECK-NEXT:       IntegerLiteral 0
  __imag__ 0;

  // FIXME: UO_Extension
}
