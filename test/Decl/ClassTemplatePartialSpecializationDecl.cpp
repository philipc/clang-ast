// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

class A {
};

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T2
template<typename T1, typename T2> class test1;

// CHECK-NEXT: ClassTemplatePartialSpecializationDecl class
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T1
// CHECK-NEXT:   TemplateArgument
// CHECK-NEXT:     TemplateTypeParmType
// CHECK-NEXT:   TemplateArgument
// CHECK-NEXT:     BuiltinType bool
template<typename T1> class test1<T1, bool>;

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test2
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T2
template<typename T1, typename T2> class test2;

// CHECK-NEXT: ClassTemplatePartialSpecializationDecl class
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T1
// CHECK-NEXT:   TemplateArgument
// CHECK-NEXT:     TemplateTypeParmType
// CHECK-NEXT:   TemplateArgument
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:   RecordType A
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:     BuiltinType int
template<typename T1> class test2<T1, bool> : A {
  int i;
};

// TODO: implicit instantiations
