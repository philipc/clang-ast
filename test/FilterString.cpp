// RUN: ast -f TheClass "%s" 2>&1 | FileCheck %s

namespace test_namespace {

class TheClass {
public:
  int theMethod(int x);
};

int TheClass::theMethod(int x) {
  return x + x;
}

int theFunction(int x) {
  return x + x;
}

}

// CHECK: CXXRecordDecl
// CHECK-NEXT:   AccessSpecDecl
// CHECK-NEXT:   CXXMethodDecl
// CHECK-NEXT:     DeclarationName theMethod
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType int
// CHECK-NEXT:       ParmVarDecl
// CHECK-NEXT:         DeclarationName x
// CHECK-NEXT:         BuiltinType int
// CHECK-NEXT: CXXMethodDecl
// CHECK-NEXT:   NestedNameSpecifier TheClass::
// CHECK-NEXT:     RecordType TheClass
// CHECK-NEXT:   DeclarationName theMethod
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:     ParmVarDecl
// CHECK-NEXT:       DeclarationName x
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
// CHECK-NOT: FunctionDecl
