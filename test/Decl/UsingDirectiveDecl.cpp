// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   UsingDirectiveDecl
// CHECK-NEXT:     NamespaceDeclRef A
// CHECK-NEXT:   UsingDirectiveDecl
// CHECK-NEXT:     NamespaceDeclRef B
// CHECK-NEXT:     NestedNameSpecifier A::
namespace A {
  namespace B {
  };
};
namespace test1 {
  using namespace A;
  using namespace A::B;
};
