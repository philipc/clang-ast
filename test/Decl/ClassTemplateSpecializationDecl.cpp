// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

class A {
};

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
// CHECK-NEXT:     TemplateTypeParmType
template<typename T> class test1;

// CHECK-NEXT: ClassTemplateSpecializationDecl class
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   TemplateSpecializationType
// CHECK-NEXT:     TemplateArgument
// CHECK-NEXT:       BuiltinType bool
template<> class test1<bool>;

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test2
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
// CHECK-NEXT:     TemplateTypeParmType
template<typename T> class test2;

// CHECK-NEXT: ClassTemplateSpecializationDecl class
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   TemplateSpecializationType
// CHECK-NEXT:     TemplateArgument
// CHECK-NEXT:       BuiltinType bool
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:   RecordType A
template<> class test2<bool> : A {
  int i;
};

// TODO: implicit instantiations
