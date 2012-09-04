// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:   TemplateTemplateParmDecl
// CHECK-NEXT:     DeclarationName T1
// CHECK-NEXT:     TemplateTypeParmDecl
// CHECK-NEXT:       DeclarationName T2
template <template <typename T2> class T1> void test1();

// CHECK-NEXT: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test2
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:   TemplateTemplateParmDecl
// CHECK-NEXT:     TemplateTypeParmDecl
template <template <typename> class> void test2();

// CHECK-NEXT: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test3
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:   TemplateTemplateParmDecl
// CHECK-NEXT:     TemplateTemplateParmDecl
// CHECK-NEXT:       TemplateTypeParmDecl
template <template <template <typename> class> class> void test3();
