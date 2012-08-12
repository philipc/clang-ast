// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  switch (0) {
  case 0:
  case 1:
    break;
  default:
    break;
  }
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     SwitchStmt
// CHECK-NEXT:       IntegerLiteral 0
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:         CaseStmt
// CHECK-NEXT:           IntegerLiteral 0
// CHECK-NEXT:         CaseStmt
// CHECK-NEXT:           IntegerLiteral 1
// CHECK-NEXT:           BreakStmt
// CHECK-NEXT:         DefaultStmt
// CHECK-NEXT:           BreakStmt

