// RUN: ast -i -f test "%s" 2>&1 | FileCheck %s

namespace A {
  int i;
  void foo(int);
  void foo(bool);
};

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   UsingDecl
// CHECK-NEXT:     NestedNameSpecifier A::
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:   UsingShadowDecl
// CHECK-NEXT:     VarDeclRef i
namespace test1 {
  using A::i;
};

// CHECK-NEXT: NamespaceDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   UsingDecl
// CHECK-NEXT:     NestedNameSpecifier A::
// CHECK-NEXT:     DeclarationName foo
// CHECK-NEXT:   UsingShadowDecl
// CHECK-NEXT:     FunctionDeclRef foo
// CHECK-NEXT:   UsingShadowDecl
// CHECK-NEXT:     FunctionDeclRef foo
namespace test2 {
  using A::foo;
};
