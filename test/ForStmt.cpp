// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  for (;;)
    ;
  for (int i = 0; int j = i; ++i)
    ;
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     ForStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     ForStmt
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl
// CHECK-NEXT:           Identifier i
// CHECK-NEXT:           BuiltinType int
// CHECK-NEXT:           IntegerLiteral 0
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl
// CHECK-NEXT:           Identifier j
// CHECK-NEXT:           BuiltinType int
// CHECK-NEXT:           ImplicitCastExpr
// CHECK-NEXT:             DeclRefExpr
// CHECK-NEXT:               DeclarationName i
// CHECK-NEXT:       ImplicitCastExpr
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:             DeclarationName j
// CHECK-NEXT:       UnaryOperator
// CHECK-NEXT:         DeclRefExpr
// CHECK-NEXT:           DeclarationName i
// CHECK-NEXT:       NullStmt
