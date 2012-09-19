// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:       ChooseExpr
  // CHECK-NEXT:         CXXBoolLiteralExpr true
  // CHECK-NEXT:         IntegerLiteral 0
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName test1
  __builtin_choose_expr(true, 0, test1);
}
