// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test() {
  for (;;)
    ;
  for (int i = 0; int j = i; ++i)
    ;
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ForStmt
// CHECK-NEXT:       NullStmt
// CHECK-NEXT:     ForStmt
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl i
// CHECK-NEXT:           Builtin int
// CHECK-NEXT:           IntegerLiteral
// CHECK-NEXT:       DeclStmt
// CHECK-NEXT:         VarDecl j
// CHECK-NEXT:           Builtin int
// CHECK-NEXT:           ImplicitCastExpr
// CHECK-NEXT:             DeclRefExpr
// CHECK-NEXT:       ImplicitCastExpr
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:       UnaryOperator
// CHECK-NEXT:         DeclRefExpr
// CHECK-NEXT:       NullStmt
