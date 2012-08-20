// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  int i, j;
  int k;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         DeclarationName i
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         DeclarationName j
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         DeclarationName k
// CHECK-NEXT:         BuiltinType int
