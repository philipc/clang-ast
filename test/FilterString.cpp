// RUN: ast -f Method "%s" 2>&1 | FileCheck %s

namespace test_namespace {

class TheClass {
public:
  int theMethod(int x) {
    return x + x;
  }
};

}

// CHECK-NOT: CXXRecordDecl
// CHECK: CXXMethodDecl theMethod
// CHECK-NEXT:   FunctionProto
// CHECK-NEXT:   Builtin int
// CHECK-NEXT:   ParmVarDecl x
// CHECK-NEXT:     Builtin int
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT:       BinaryOperator
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
