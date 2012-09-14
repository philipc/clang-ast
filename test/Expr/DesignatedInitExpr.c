// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

struct A {
  int i;
  int j;
};

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   ElaboratedType
// CHECK-NEXT:     RecordType A
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       FieldDeclRef i
// CHECK-NEXT:       IntegerLiteral 1
struct A test1 = { .i = 1 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   ConstantArrayType
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:     IntegerLiteral 5
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       IntegerLiteral 1
// CHECK-NEXT:       IntegerLiteral 0
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       IntegerLiteral 10
// CHECK-NEXT:       IntegerLiteral 2
// CHECK-NEXT:       IntegerLiteral 4
int test2[5] = { [0] = 1, [2 ... 4] = 10 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   ConstantArrayType
// CHECK-NEXT:     ElaboratedType
// CHECK-NEXT:       RecordType A
// CHECK-NEXT:     IntegerLiteral 5
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       FieldDeclRef j
// CHECK-NEXT:       IntegerLiteral 2
// CHECK-NEXT:       IntegerLiteral 1
struct A test3[5] = { [1].j = 2 };
