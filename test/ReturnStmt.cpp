// RUN: ast -f test "%s" 2>&1 | FileCheck %s

void test1() {
  return;
};

int test2() {
  return 4;
};

// CHECK: FunctionDecl test1
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT: FunctionDecl test2
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin int
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT:       IntegerLiteral
