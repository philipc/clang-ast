// RUN: ast "%s" 2>&1 | FileCheck %s

namespace test_namespace {

class TheClass {
public:
  int theMethod(int x) {
    return x + x;
  }
};

}

// CHECK: NamespaceDecl test_namespace
// CHECK-NEXT:   CXXRecordDecl TheClass
// CHECK-NEXT:     AccessSpecDecl
// CHECK-NEXT:     CXXMethodDecl theMethod
// CHECK-NEXT:       FunctionProto
// CHECK-NEXT:       Builtin int
// CHECK-NEXT:       ParmVarDecl x
// CHECK-NEXT:         Builtin int
// CHECK-NEXT:       CompoundStmt
// CHECK-NEXT:         ReturnStmt
// CHECK-NEXT:           BinaryOperator
// CHECK-NEXT:             ImplicitCastExpr
// CHECK-NEXT:               DeclRefExpr
// CHECK-NEXT:             ImplicitCastExpr
// CHECK-NEXT:               DeclRefExpr
