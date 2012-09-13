// RUN: ast -f test "%s" 2>&1 | FileCheck %s

struct A {
  int i;
};

// CHECK:   CompoundStmt
void test() {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:         BuiltinType int
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName j
  // CHECK-NEXT:         BuiltinType int
  int i, j;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName k
  // CHECK-NEXT:         BuiltinType int
  int k;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName a
  // CHECK-NEXT:         ElaboratedType
  // CHECK-NEXT:           RecordType A
  // CHECK-NEXT:         CXXConstructExpr
  struct A a;

  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       CXXRecordDecl struct
  // CHECK-NEXT:         DeclarationName B
  // CHECK-NEXT:         FieldDecl
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:           BuiltinType int
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName b
  // CHECK-NEXT:         ElaboratedType
  // CHECK-NEXT:           RecordType B
  // CHECK-NEXT:         CXXConstructExpr
  struct B { int i; } b;
};

