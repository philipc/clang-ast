// RUN: ast -f test -- -Wno-unused-value "%s" 2>&1 | FileCheck %s

struct A {
  int i1;
  static int i2;
  template <typename T> void f1();
  template <typename T> static void f2();

  // CHECK:   CompoundStmt
  void test1() {
    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       DeclarationName i1
    // CHECK-NEXT:       CXXThisExpr
    i1;

    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       DeclarationName i1
    // CHECK-NEXT:       CXXThisExpr
    this->i1;

    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       NestedNameSpecifier A::
    // CHECK-NEXT:         RecordType A
    // CHECK-NEXT:       DeclarationName i1
    // CHECK-NEXT:       CXXThisExpr
    A::i1;

    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       NestedNameSpecifier A::
    // CHECK-NEXT:         RecordType A
    // CHECK-NEXT:       DeclarationName i1
    // CHECK-NEXT:       CXXThisExpr
    this->A::i1;

    // CHECK-NEXT:     DeclRefExpr
    // CHECK-NEXT:       DeclarationName i2
    i2;

    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       DeclarationName i2
    // CHECK-NEXT:       CXXThisExpr
    this->i2;

    // CHECK-NEXT:     DeclRefExpr
    // CHECK-NEXT:       NestedNameSpecifier A::
    // CHECK-NEXT:         RecordType A
    // CHECK-NEXT:       DeclarationName i2
    A::i2;

    // CHECK-NEXT:     MemberExpr
    // CHECK-NEXT:       NestedNameSpecifier A::
    // CHECK-NEXT:         RecordType A
    // CHECK-NEXT:       DeclarationName i2
    // CHECK-NEXT:       CXXThisExpr
    this->A::i2;

    // CHECK-NEXT:     CXXMemberCallExpr
    // CHECK-NEXT:       MemberExpr
    // CHECK-NEXT:         DeclarationName f1
    // CHECK-NEXT:         TemplateArgument
    // CHECK-NEXT:           BuiltinType int
    // CHECK-NEXT:         CXXThisExpr
    f1<int>();

    // CHECK-NEXT:     CXXMemberCallExpr
    // CHECK-NEXT:       MemberExpr
    // CHECK-NEXT:         DeclarationName f1
    // CHECK-NEXT:         TemplateArgument
    // CHECK-NEXT:           BuiltinType int
    // CHECK-NEXT:         CXXThisExpr
    this->f1<int>();

    // CHECK-NEXT:     CXXMemberCallExpr
    // CHECK-NEXT:       MemberExpr
    // CHECK-NEXT:         NestedNameSpecifier A::
    // CHECK-NEXT:           RecordType A
    // CHECK-NEXT:         DeclarationName f1
    // CHECK-NEXT:         TemplateArgument
    // CHECK-NEXT:           BuiltinType int
    // CHECK-NEXT:         CXXThisExpr
    A::f1<int>();

    // CHECK-NEXT:     CXXMemberCallExpr
    // CHECK-NEXT:       MemberExpr
    // CHECK-NEXT:         NestedNameSpecifier A::
    // CHECK-NEXT:           RecordType A
    // CHECK-NEXT:         DeclarationName f1
    // CHECK-NEXT:         TemplateArgument
    // CHECK-NEXT:           BuiltinType int
    // CHECK-NEXT:         CXXThisExpr
    this->A::f1<int>();

    // CHECK-NEXT:     CallExpr
    // CHECK-NEXT:       ImplicitCastExpr
    // CHECK-NEXT:         DeclRefExpr
    // CHECK-NEXT:           DeclarationName f2
    // CHECK-NEXT:           TemplateArgument
    // CHECK-NEXT:             BuiltinType int
    f2<int>();

    // CHECK-NEXT:     CallExpr
    // CHECK-NEXT:       ImplicitCastExpr
    // CHECK-NEXT:         MemberExpr
    // CHECK-NEXT:           DeclarationName f2
    // CHECK-NEXT:           TemplateArgument
    // CHECK-NEXT:             BuiltinType int
    // CHECK-NEXT:           CXXThisExpr
    this->f2<int>();

    // CHECK-NEXT:     CallExpr
    // CHECK-NEXT:       ImplicitCastExpr
    // CHECK-NEXT:         DeclRefExpr
    // CHECK-NEXT:           NestedNameSpecifier A::
    // CHECK-NEXT:             RecordType A
    // CHECK-NEXT:           DeclarationName f2
    // CHECK-NEXT:           TemplateArgument
    // CHECK-NEXT:             BuiltinType int
    A::f2<int>();

    // CHECK-NEXT:     CallExpr
    // CHECK-NEXT:       ImplicitCastExpr
    // CHECK-NEXT:         MemberExpr
    // CHECK-NEXT:           NestedNameSpecifier A::
    // CHECK-NEXT:             RecordType A
    // CHECK-NEXT:           DeclarationName f2
    // CHECK-NEXT:           TemplateArgument
    // CHECK-NEXT:             BuiltinType int
    // CHECK-NEXT:           CXXThisExpr
    this->A::f2<int>();
  }
};
