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
// CHECK: CXXMethodDecl
// CHECK-NEXT:   DeclarationName theMethod
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:     ParmVarDecl
// CHECK-NEXT:       Identifier x
// CHECK-NEXT:       BuiltinType int
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT:       BinaryOperator
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:             DeclarationName x
// CHECK-NEXT:         ImplicitCastExpr
// CHECK-NEXT:           DeclRefExpr
// CHECK-NEXT:             DeclarationName x
