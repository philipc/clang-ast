// RUN: ast -f test "%s" 2>&1 | FileCheck %s

struct A {
  int i;
  int j;
};

union B {
  int i;
  long j;
};

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   ElaboratedType
// CHECK-NEXT:     RecordType A
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     IntegerLiteral 1
// CHECK-NEXT:     IntegerLiteral 2
struct A test1 = { 1, 2 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   ElaboratedType
// CHECK-NEXT:     RecordType A
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       FieldDeclRef j
// CHECK-NEXT:       IntegerLiteral 2
struct A test2 = { .j = 2 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   ElaboratedType
// CHECK-NEXT:     RecordType B
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     IntegerLiteral 1
union B test3 = { 1 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test4
// CHECK-NEXT:   ElaboratedType
// CHECK-NEXT:     RecordType B
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     DesignatedInitExpr
// CHECK-NEXT:       FieldDeclRef j
// CHECK-NEXT:       ImplicitCastExpr IntegralCast
// CHECK-NEXT:         IntegerLiteral 2
union B test4 = { .j = 2 };

// CHECK-NEXT: VarDecl
// CHECK-NEXT:   DeclarationName test5
// CHECK-NEXT:   ConstantArrayType
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:     IntegerLiteral 5
// CHECK-NEXT:   InitListExpr
// CHECK-NEXT:     IntegerLiteral 1
// CHECK-NEXT:     IntegerLiteral 2
// CHECK-NEXT:     IntegerLiteral 3
int test5[5] = { 1, 2, 3 };
