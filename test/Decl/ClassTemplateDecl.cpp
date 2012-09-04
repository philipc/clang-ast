// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template<class T> class test1;

// TODO: implicit instantiations
