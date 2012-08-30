// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: CXXRecordDecl struct
// CHECK-NEXT:   DeclarationName test
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName b1
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName b2
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:     CXXBoolLiteralExpr true
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i1
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:     IntegerLiteral 1
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     DeclarationName i2
// CHECK-NEXT:     ConstantArrayType
// CHECK-NEXT:       BuiltinType int
// CHECK-NEXT:       IntegerLiteral 3
// CHECK-NEXT:     InitListExpr
// CHECK-NEXT:       IntegerLiteral 0
// CHECK-NEXT:       IntegerLiteral 1
// CHECK-NEXT:       IntegerLiteral 2
// CHECK-NEXT:   CXXRecordDecl struct
// CHECK-NEXT:     FieldDecl
// CHECK-NEXT:       DeclarationName i3
// CHECK-NEXT:       BuiltinType int
// FIXME: why is the anonymous FieldDecl implicit?
struct test {
  bool b1;
  bool b2 = true;
  int i1:1;
  int i2[3] = { 0, 1, 2 };
  struct {
    int i3;
  };
};
