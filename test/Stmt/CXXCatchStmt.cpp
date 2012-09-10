// RUN: ast -f test "%s" 2>&1 | FileCheck %s

class E {
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     CXXTryStmt
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:       CXXCatchStmt
// CHECK-NEXT:         VarDecl
// CHECK-NEXT:           DeclarationName e
// CHECK-NEXT:           RecordType E
// CHECK-NEXT:         CompoundStmt
// CHECK-NEXT:       CXXCatchStmt
// CHECK-NEXT:         CompoundStmt
void test() {
  try {
  }
  catch (E e) {
  }
  catch (...) {
  }
};
