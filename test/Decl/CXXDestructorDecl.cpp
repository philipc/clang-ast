// RUN: ast -f test "%s" 2>&1 | FileCheck %s

class test1 {
  // CHECK:   CXXDestructorDecl
  // CHECK-NEXT:     DeclarationName ~test1
  // CHECK-NEXT:     FunctionProtoType
  // CHECK-NEXT:       BuiltinType void
  ~test1();
};

// CHECK: CXXDestructorDecl
// CHECK-NEXT:   NestedNameSpecifier test1::
// CHECK-NEXT:     RecordType test1
// CHECK-NEXT:   DeclarationName ~test1
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:   CompoundStmt
test1::~test1() {
}

class test2 {
  // CHECK:   CXXDestructorDecl
  // CHECK-NEXT:     DeclarationName ~test2
  // CHECK-NEXT:     FunctionProtoType
  // CHECK-NEXT:       BuiltinType void
  // CHECK-NEXT:     CompoundStmt
  ~test2() {
  }
};
