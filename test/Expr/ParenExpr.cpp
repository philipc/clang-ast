// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
// CHECK-NEXT:   ParenExpr
// CHECK-NEXT:     IntegerLiteral 1
void test1() {
  (1);
}
