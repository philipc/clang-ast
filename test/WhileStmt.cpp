// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  while (true)
    ;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     WhileStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
// CHECK-NEXT:       NullStmt
