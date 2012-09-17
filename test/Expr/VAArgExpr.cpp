// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
void test1(...) {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName ap
  // CHECK-NEXT:         TypedefType
  __builtin_va_list ap;

  // CHECK-NEXT:     VAArgExpr
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName ap
  __builtin_va_arg(ap, int);
}
