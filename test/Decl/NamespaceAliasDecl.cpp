// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

namespace A {
  namespace B {
  };
};

// CHECK: NamespaceAliasDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   NamespaceDeclRef A
namespace test1 = A;

// CHECK-NEXT: NamespaceAliasDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   NamespaceDeclRef B
namespace test2 = A::B;
