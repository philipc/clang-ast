// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: CXXRecordDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   CXXConversionDecl
// CHECK-NEXT:     DeclarationName operator _Bool
// CHECK-NEXT:       BuiltinType bool
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType bool
class test1 {
  operator bool();
};

// FIXME: should CXXConstructorDecl and CXXDestructorDecl also include the type?
