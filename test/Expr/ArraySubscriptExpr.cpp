// RUN: ast -f test -- -Wno-warn-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:         BuiltinType int
  // CHECK-NEXT:         IntegerLiteral 0
  int i = 0;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName p
  // CHECK-NEXT:         PointerType
  // CHECK-NEXT:           BuiltinType int
  // CHECK-NEXT:         ImplicitCastExpr NullToPointer
  // CHECK-NEXT:           IntegerLiteral 0
  int *p = 0;

  // CHECK-NEXT:     ArraySubscriptExpr
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName p
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  p[i];

  // CHECK-NEXT:     ArraySubscriptExpr
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName p
  i[p];
}
