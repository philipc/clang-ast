// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  l:;
  void *p = &&l;
  goto *p;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     LabelStmt
// CHECK-NEXT:       Identifier l
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         Identifier p
// CHECK-NEXT:         PointerType
// CHECK-NEXT:           BuiltinType void
// CHECK-NEXT:         AddrLabelExpr
// CHECK-NEXT:     IndirectGotoStmt
// CHECK-NEXT:       ImplicitCastExpr
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:             DeclarationName p
