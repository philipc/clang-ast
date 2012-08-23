// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   VarDecl
// CHECK-NEXT:     DeclarationName b1
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:   NamespaceDecl
// CHECK-NEXT:   NamespaceDecl
// CHECK-NEXT:     VarDecl
// CHECK-NEXT:       DeclarationName b2
// CHECK-NEXT:       BuiltinType bool
namespace test1 {
  bool b1;
  namespace {
  };
  namespace {
    bool b2;
  };
};
