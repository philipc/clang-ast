// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  {
  }
  return;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     CompoundStmt
// CHECK-NEXT:     ReturnStmt
