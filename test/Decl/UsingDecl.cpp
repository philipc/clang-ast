// RUN: ast -f test "%s" 2>&1 | FileCheck %s

namespace A {
  int i;
};

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   UsingDecl
// CHECK-NEXT:     NestedNameSpecifier A::
// CHECK-NEXT:     DeclarationName i
namespace test1 {
  using A::i;
};
