// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

struct A {
  int i;
};

// CHECK:   CompoundStmt
void test1() {
  // CHECK-NEXT:     ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:       CompoundLiteralExpr
  // CHECK-NEXT:         ElaboratedType
  // CHECK-NEXT:           RecordType A
  // CHECK-NEXT:         InitListExpr
  // CHECK-NEXT:           IntegerLiteral 1
  (struct A) { 1 };

  // CHECK-NEXT:     ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:       CompoundLiteralExpr
  // CHECK-NEXT:         ElaboratedType
  // CHECK-NEXT:           RecordType B
  // CHECK-NEXT:         InitListExpr
  // CHECK-NEXT:           IntegerLiteral 1
  // CHECK-NEXT:         RecordDecl struct
  // CHECK-NEXT:           DeclarationName B
  // CHECK-NEXT:           FieldDecl
  // CHECK-NEXT:             DeclarationName i
  // CHECK-NEXT:             BuiltinType int
  (struct B { int i; }) { 1 };

  // CHECK-NEXT:     ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:       CompoundLiteralExpr
  // CHECK-NEXT:         ElaboratedType
  // CHECK-NEXT:           RecordType <anon>
  // CHECK-NEXT:         InitListExpr
  // CHECK-NEXT:           IntegerLiteral 1
  // CHECK-NEXT:         RecordDecl struct
  // CHECK-NEXT:           FieldDecl
  // CHECK-NEXT:             DeclarationName i
  // CHECK-NEXT:             BuiltinType int
  (struct { int i; }) { 1 };
};
