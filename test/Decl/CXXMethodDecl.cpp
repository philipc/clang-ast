// RUN: ast -f test "%s" 2>&1 | FileCheck %s

class A {

  // CHECK: CXXMethodDecl
  // CHECK-NEXT:   DeclarationName test1
  // CHECK-NEXT:   FunctionProtoType
  // CHECK-NEXT:     BuiltinType void
  void test1();

  // CHECK: CXXMethodDecl
  // CHECK-NEXT:   DeclarationName test2
  // CHECK-NEXT:   FunctionProtoType
  // CHECK-NEXT:     BuiltinType void
  // CHECK-NEXT:     ParmVarDecl
  // CHECK-NEXT:       DeclarationName a
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:   CompoundStmt
  void test2(int a) {
  }

};

// CHECK: CXXMethodDecl
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:     RecordType
// CHECK-NEXT:       Identifier A
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:   CompoundStmt
void A::test1() {
}
