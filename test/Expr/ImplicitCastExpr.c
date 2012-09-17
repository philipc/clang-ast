// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

void test1() {
  int i;
  int *pi;
  void *pv;
  _Atomic(int) ai;

  // CHECK:     ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  i;

  // CHECK-NEXT:     BinaryOperator
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName pi
  // CHECK-NEXT:       ImplicitCastExpr BitCast
  // CHECK-NEXT:         ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName pv
  pi = pv;

  // CHECK-NEXT:     ImplicitCastExpr AtomicToNonAtomic
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName ai
  ai;
}
