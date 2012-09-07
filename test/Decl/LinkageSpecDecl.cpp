// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test
// CHECK-NEXT:   LinkageSpecDecl C
// CHECK-NEXT:     FunctionDecl
// CHECK-NEXT:       DeclarationName foo1
// CHECK-NEXT:       FunctionProtoType
// CHECK-NEXT:         BuiltinType void
// CHECK-NEXT:   LinkageSpecDecl C++
// CHECK-NEXT:     FunctionDecl
// CHECK-NEXT:       DeclarationName foo2
// CHECK-NEXT:       FunctionProtoType
// CHECK-NEXT:         BuiltinType
namespace test {
  extern "C" void foo1();
  extern "C++"void foo2();
}
