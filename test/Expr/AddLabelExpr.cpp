// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
void test() {
  // CHECK-NEXT:     LabelStmt
  // CHECK-NEXT:       LabelDeclRef l
  // CHECK-NEXT:       NullStmt
  l:;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName p
  // CHECK-NEXT:         PointerType
  // CHECK-NEXT:           BuiltinType void
  // CHECK-NEXT:         AddrLabelExpr
  // CHECK-NEXT:           LabelDeclRef l
  void *p = &&l;
};
