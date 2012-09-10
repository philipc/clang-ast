// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
// CHECK-NEXT:     CXXTryStmt
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:       CXXCatchStmt
// CHECK-NEXT:         CompoundStmt
void test() {
  try {
  }
  catch (...) {
  }
};
