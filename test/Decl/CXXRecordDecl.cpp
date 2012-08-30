// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: CXXRecordDecl class
// CHECK-NEXT:   DeclarationName test1
class test1 {

  // CHECK-NEXT:   CXXRecordDecl class
  // CHECK-NEXT:     FieldDecl
  // CHECK-NEXT:       DeclarationName i
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:   FieldDecl
  // CHECK-NEXT:     DeclarationName test2
  // CHECK-NEXT:     ElaboratedType
  // CHECK-NEXT:       RecordType <anon>
  class {
    int i;
  } test2;
};

// CHECK-NEXT: CXXRecordDecl class
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName c
// CHECK-NEXT:     IncompleteArrayType
// CHECK-NEXT:       BuiltinType char
class test3 {
  int i;
  char c[];
};

class A {
};

// CHECK-NEXT: CXXRecordDecl class
// CHECK-NEXT:   DeclarationName test4
// CHECK-NEXT:   RecordType A
class test4 : A {
};

// CHECK-NEXT: CXXRecordDecl class
// CHECK-NEXT:   DeclarationName test5
// CHECK-NEXT:   RecordType A
class test5 : virtual A {
};
