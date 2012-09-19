// RUN: ast -i -f test "%s" 2>&1 | FileCheck %s

typedef void (*foo)();

template<typename T> class A {
  T t;
};

namespace test1 {
  // CHECK:   ClassTemplateSpecializationDecl class
  // CHECK-NEXT:     DeclarationName A
  // CHECK-NEXT:     TemplateSpecializationType
  // CHECK-NEXT:       TemplateArgument
  // CHECK-NEXT:         TypedefType
  // CHECK-NEXT:     CXXRecordDecl class
  // CHECK-NEXT:       DeclarationName A
  // CHECK-NEXT:     FieldDecl
  // CHECK-NEXT:       DeclarationName t
  // CHECK-NEXT:       SubstTemplateTypeParmType
  // CHECK-NEXT:         PointerType
  // CHECK-NEXT:           FunctionProtoType
  // CHECK-NEXT:             BuiltinType void
  template class A<foo>;
}
