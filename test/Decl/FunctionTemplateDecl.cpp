// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template<class T> void test1();

// TODO: implicit instantiations
