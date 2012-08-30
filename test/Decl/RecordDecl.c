// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: RecordDecl union
// CHECK-NEXT:   DeclarationName test1
union test1 {

  // CHECK-NEXT:   RecordDecl struct
  // CHECK-NEXT:     FieldDecl
  // CHECK-NEXT:       DeclarationName i
  // CHECK-NEXT:       BuiltinType int
  // CHECK-NEXT:   FieldDecl
  // CHECK-NEXT:     DeclarationName test2
  // CHECK-NEXT:     ElaboratedType
  // CHECK-NEXT:       RecordType <anon>
  struct {
    int i;
  } test2;
};

// CHECK-NEXT: RecordDecl struct
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName c
// CHECK-NEXT:     IncompleteArrayType
// CHECK-NEXT:       BuiltinType char
struct test3 {
  int i;
  char c[];
};

// CHECK-NEXT: RecordDecl struct
// CHECK-NEXT:   DeclarationName test4
// CHECK-NEXT:   RecordDecl struct
// CHECK-NEXT:     FieldDecl
// CHECK-NEXT:       DeclarationName i
// CHECK-NEXT:       BuiltinType int
struct test4 {
  struct {
    int i;
  };
};
