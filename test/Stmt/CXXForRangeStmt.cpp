// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

extern int a[1];

// FIXME: RAV should traverse getLoopVariable() instead of getLoopVarStmt()
// CHECK:   CompoundStmt
// CHECK-NEXT:     CXXForRangeStmt
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl
// CHECK-NEXT:           DeclarationName x
// CHECK-NEXT:           LValueReferenceType
// CHECK-NEXT:             BuiltinType int
// CHECK-NEXT:       DeclRefExpr
// CHECK-NEXT:         DeclarationName a
// CHECK-NEXT:       NullStmt
void test() {
  for (int &x : a)
    ;
};

// TODO: implicit version
