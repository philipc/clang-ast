// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void f(...);

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     CallExpr
  // CHECK-NEXT:       ImplicitCastExpr FunctionToPointerDecay
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName f
  f();

  // CHECK-NEXT:     CallExpr
  // CHECK-NEXT:       ImplicitCastExpr FunctionToPointerDecay
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName f
  // CHECK-NEXT:       IntegerLiteral 0
  // CHECK-NEXT:       IntegerLiteral 1
  f(0, 1);
}
