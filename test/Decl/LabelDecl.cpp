// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  __label__ l;
  l: goto l;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       LabelDecl
// CHECK-NEXT:         DeclarationName l
// CHECK-NEXT:     LabelStmt
// CHECK-NEXT:       LabelDeclRef l
// CHECK-NEXT:       GotoStmt
// CHECK-NEXT:         LabelDeclRef l
