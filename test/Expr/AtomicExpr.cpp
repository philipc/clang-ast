// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:         AtomicType
  // CHECK-NEXT:           BuiltinType int
  _Atomic(int) i;

  // CHECK-NEXT:     AtomicExpr __c11_atomic_init
  // CHECK-NEXT:       UnaryOperator &
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       IntegerLiteral 0
  __c11_atomic_init(&i, 0);
}
