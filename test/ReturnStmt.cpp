// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
void test1() {
  return;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT:       IntegerLiteral 4
int test2() {
  return 4;
};
