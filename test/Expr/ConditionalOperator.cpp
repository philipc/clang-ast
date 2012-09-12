// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:       ConditionalOperator
  // CHECK-NEXT:         CXXBoolLiteralExpr true
  // CHECK-NEXT:         IntegerLiteral 0
  // CHECK-NEXT:         IntegerLiteral 1
  true ? 0 : 1;

  // CHECK-NEXT:       BinaryConditionalOperator
  // CHECK-NEXT:         IntegerLiteral 0
  // CHECK-NEXT:         ImplicitCastExpr IntegralToBoolean
  // CHECK-NEXT:           OpaqueValueExpr
  // CHECK-NEXT:         OpaqueValueExpr
  // CHECK-NEXT:         IntegerLiteral 1
  0 ?: 1;
}
