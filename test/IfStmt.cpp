// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  if (true)
    ;

  if (true)
    ;
  else
    ;

  if (bool b = true)
    ;
  else
    ;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       CXXBoolLiteralExpr
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       CXXBoolLiteralExpr
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl b
// CHECK-NEXT:           Builtin bool
// CHECK-NEXT:           CXXBoolLiteralExpr
// CHECK-NEXT:       ImplicitCastExpr
// CHECK-NEXT:         DeclRefExpr
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       NullStmt
