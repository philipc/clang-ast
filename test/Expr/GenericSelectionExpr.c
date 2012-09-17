// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
void test1() {
  // CHECK-NEXT:     GenericSelectionExpr
  // CHECK-NEXT:       IntegerLiteral 0
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       IntegerLiteral 1
  // CHECK-NEXT:       BuiltinType double
  // CHECK-NEXT:       IntegerLiteral 2
  // CHECK-NEXT:       IntegerLiteral 3
  _Generic(0, int: 1, double: 2, default: 3);
}
