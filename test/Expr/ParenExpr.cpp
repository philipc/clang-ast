// RUN: ast -f test -- -Wno-warn-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
// CHECK-NEXT:   ParenExpr
// CHECK-NEXT:     IntegerLiteral 1
void test1() {
  (1);
}
