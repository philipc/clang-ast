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

// CHECK:   CompoundStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       CXXBoolLiteralExpr true
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     IfStmt
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl
// CHECK-NEXT:           DeclarationName b
// CHECK-NEXT:           BuiltinType bool
// CHECK-NEXT:           CXXBoolLiteralExpr true
// CHECK-NEXT:       ImplicitCastExpr LValueToRValue
// CHECK-NEXT:         DeclRefExpr
// CHECK-NEXT:           DeclarationName b
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:       NullStmt
