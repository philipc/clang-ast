// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
void test() {
  // CHECK:     StmtExpr
  // CHECK-NEXT:       CompoundStmt
  // CHECK-NEXT:         IntegerLiteral 0
  ({ 0; });
};
