// RUN: ast -i -f test "%s" 2>&1 | FileCheck %s

void test() {
  union { int i; };
}

// CHECK: CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         ElaboratedType
// CHECK-NEXT:           RecordType <anon>
// CHECK-NEXT:         CXXConstructExpr
