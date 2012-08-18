// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  ;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     NullStmt
