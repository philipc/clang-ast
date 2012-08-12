// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  l: goto l;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     LabelStmt
// CHECK-NEXT:       Identifier l
// CHECK-NEXT:       GotoStmt
// CHECK-NEXT:         Identifier l
