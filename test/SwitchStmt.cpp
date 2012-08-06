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

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     SwitchStmt
// CHECK-NEXT:       IntegerLiteral
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:         CaseStmt
// CHECK-NEXT:           IntegerLiteral
// CHECK-NEXT:         CaseStmt
// CHECK-NEXT:           IntegerLiteral
// CHECK-NEXT:           BreakStmt
// CHECK-NEXT:         DefaultStmt
// CHECK-NEXT:           BreakStmt

