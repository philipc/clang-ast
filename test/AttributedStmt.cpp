// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

void test() {
  switch (0) {
  case 0:
    [[clang::fallthrough]];
  }
};

// CHECK: FunctionDecl test
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     SwitchStmt
// CHECK-NEXT:       IntegerLiteral 0
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:         CaseStmt
// CHECK-NEXT:           IntegerLiteral 0
// CHECK-NEXT:           AttributedStmt
// CHECK-NEXT:             NullStmt
