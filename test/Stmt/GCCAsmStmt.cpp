// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         DeclarationName a
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         DeclarationName b
// CHECK-NEXT:         BuiltinType int
void test() {
  int a, b;

  // CHECK-NEXT:     GCCAsmStmt
  // CHECK-NEXT:       StringLiteral "movl 1, %eax;"
  asm("movl 1, %eax;");

  // CHECK-NEXT:     GCCAsmStmt
  // CHECK-NEXT:       StringLiteral "movl 1, %%eax;"
  // CHECK-NEXT:       StringLiteral "%eax"
  asm("movl 1, %%eax;":::"%eax");

  // CHECK-NEXT:     GCCAsmStmt
  // CHECK-NEXT:       StringLiteral "movl %1, %%eax;movl %%eax, %0;"
  // CHECK-NEXT:       StringLiteral "r"
  // CHECK-NEXT:       StringLiteral "=r"
  // CHECK-NEXT:       StringLiteral "%eax"
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName b
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName a
  asm("movl %1, %%eax;"
      "movl %%eax, %0;"
      :"=r"(b)
      :"r"(a)
      :"%eax"
     );
};

