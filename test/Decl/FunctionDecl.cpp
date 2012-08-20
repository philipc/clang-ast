// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: FunctionDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:     ParmVarDecl
// CHECK-NEXT:       DeclarationName a
// CHECK-NEXT:       BuiltinType int
void test1(int a);

// CHECK: FunctionDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:   CompoundStmt
void test2(void) {
}

// CHECK: FunctionDecl
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
namespace A {
  void test3();
};

// CHECK: FunctionDecl
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:   CompoundStmt
void A::test3() {
}
