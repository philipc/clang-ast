// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

void test() {
  switch (0) {
  case 0:
    [[clang::fallthrough]];
  }
};

// CHECK:         CaseStmt
// CHECK-NEXT:           IntegerLiteral 0
// CHECK-NEXT:           AttributedStmt
// CHECK-NEXT:             NullStmt
