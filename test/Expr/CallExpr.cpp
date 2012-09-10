// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void f(...);

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     CallExpr
  // CHECK-NEXT:       ImplicitCastExpr
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName f
  f();

  // CHECK-NEXT:     CallExpr
  // CHECK-NEXT:       ImplicitCastExpr
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName f
  // CHECK-NEXT:       ImplicitCastExpr
  // CHECK-NEXT:         CXXBoolLiteralExpr true
  // CHECK-NEXT:       ImplicitCastExpr
  // CHECK-NEXT:         CXXBoolLiteralExpr false
  f(true, false);
}
