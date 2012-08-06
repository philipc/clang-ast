// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  l:;
  void *p = &&l;
  goto *p;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     LabelStmt l
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl p
// CHECK-NEXT:         Pointer
// CHECK-NEXT:         Builtin void
// CHECK-NEXT:         AddrLabelExpr
// CHECK-NEXT:     IndirectGotoStmt
// CHECK-NEXT:       ImplicitCastExpr
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
