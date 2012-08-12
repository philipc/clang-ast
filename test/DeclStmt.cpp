// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  int i, j;
  int k;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         Identifier i
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         Identifier j
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         Identifier k
// CHECK-NEXT:         BuiltinType int
