// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
void test1() {
  // CHECK-NEXT:     GNUNullExpr
  __null;
}
