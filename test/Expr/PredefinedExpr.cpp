// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

// CHECK:   CompoundStmt
// CHECK-NEXT:     PredefinedExpr __func__
// CHECK-NEXT:     PredefinedExpr __FUNCTION__
void test() {
  __func__;
  __FUNCTION__;
};
