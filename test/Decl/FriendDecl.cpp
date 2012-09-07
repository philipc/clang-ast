// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: ClassTemplateDecl
// CHECK-NEXT:   CXXRecordDecl class
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:     FriendDecl
// CHECK-NEXT:       FunctionDecl
// CHECK-NEXT:         DeclarationName foo
// CHECK-NEXT:         FunctionProtoType
// CHECK-NEXT:           BuiltinType int
// CHECK-NEXT:     FriendDecl
// CHECK-NEXT:       ElaboratedType
// CHECK-NEXT:         RecordType A
// CHECK-NEXT:     FriendDecl
// CHECK-NEXT:       TemplateTypeParmType
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template <typename T> class test1 {
  friend int foo();
  friend class A;
  friend T;
};
