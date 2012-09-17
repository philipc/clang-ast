// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

struct S {
  float f;
  double d;
};
struct T {
  int i;
  struct S s[10];
};

// FIXME: not all the details are here yet
// CHECK: CompoundStmt
// CHECK-NEXT:   OffsetOfExpr
// CHECK-NEXT:     ElaboratedType
// CHECK-NEXT:       RecordType T
// CHECK-NEXT:     IntegerLiteral 2
void test1() {
  __builtin_offsetof(struct T, s[2].d);
}
