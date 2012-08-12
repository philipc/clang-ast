// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  for (;;)
    break;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     ForStmt
// CHECK-NEXT:       BreakStmt
