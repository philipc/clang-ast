// RUN: ast -f test -- -std=c++11 -Wno-unused "%s" 2>&1 | FileCheck %s

struct S {
  float f;
  double d;
};
struct T {
  int i;
  struct S s[10];
};

struct T t;

// FIXME: not all the details are here yet
// CHECK: CompoundStmt
// CHECK-NEXT:   UnaryExprOrTypeTraitExpr sizeof
// CHECK-NEXT:     ElaboratedType
// CHECK-NEXT:       RecordType T
// CHECK-NEXT:   UnaryExprOrTypeTraitExpr alignof
// CHECK-NEXT:     DeclRefExpr
// CHECK-NEXT:       DeclarationName t
void test1() {
  sizeof(struct T);
  alignof t;
}
