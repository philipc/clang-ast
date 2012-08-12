// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  do
    ;
  while (true);
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     DoStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
