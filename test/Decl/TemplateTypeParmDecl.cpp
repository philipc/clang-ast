// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
// CHECK-NEXT:     TemplateTypeParmType
template<class T> class test1;

// CHECK-NEXT: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test2
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
// CHECK-NEXT:     TemplateTypeParmType
template<typename T> class test2;

// CHECK-NEXT: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test3
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
// CHECK-NEXT:     TemplateTypeParmType
// CHECK-NEXT:     BuiltinType bool
template<typename T=bool> class test3;

// CHECK-NEXT: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test4
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     TemplateTypeParmType
template<typename> class test4;
