// RUN: ast -f test -- -Wno-unused "%s" 2>&1 | FileCheck %s

class A {
};

// CHECK: CompoundStmt
void test1() {
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName f
  // CHECK-NEXT:         MemberPointerType
  // CHECK-NEXT:           RecordType A
  // CHECK-NEXT:           ParenType
  // CHECK-NEXT:             FunctionProtoType
  // CHECK-NEXT:               BuiltinType void
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName a
  // CHECK-NEXT:         RecordType A
  // CHECK-NEXT:         CXXConstructExpr
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName pa
  // CHECK-NEXT:         PointerType
  // CHECK-NEXT:           RecordType A
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:         BuiltinType int
  // CHECK-NEXT:     DeclStmt
  // CHECK-NEXT:       VarDecl
  // CHECK-NEXT:         DeclarationName j
  // CHECK-NEXT:         BuiltinType int
  void (A::* f)();
  A a;
  A *pa;
  int i;
  int j;

  // CHECK-NEXT:     CXXMemberCallExpr
  // CHECK-NEXT:       ParenExpr
  // CHECK-NEXT:         BinaryOperator .*
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName a
  // CHECK-NEXT:           ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:             DeclRefExpr
  // CHECK-NEXT:               DeclarationName f
  (a.*f)();

  // CHECK-NEXT:     CXXMemberCallExpr
  // CHECK-NEXT:       ParenExpr
  // CHECK-NEXT:         BinaryOperator ->*
  // CHECK-NEXT:           ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:             DeclRefExpr
  // CHECK-NEXT:               DeclarationName pa
  // CHECK-NEXT:           ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:             DeclRefExpr
  // CHECK-NEXT:               DeclarationName f
  (pa->*f)();

  // CHECK-NEXT:     BinaryOperator *
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i * j;

  // CHECK-NEXT:     BinaryOperator /
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i / j;

  // CHECK-NEXT:     BinaryOperator %
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i % j;

  // CHECK-NEXT:     BinaryOperator +
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i + j;

  // CHECK-NEXT:     BinaryOperator -
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i - j;

  // CHECK-NEXT:     BinaryOperator <<
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i << j;

  // CHECK-NEXT:     BinaryOperator >>
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i >> j;

  // CHECK-NEXT:     BinaryOperator <
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i < j;

  // CHECK-NEXT:     BinaryOperator >
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i > j;

  // CHECK-NEXT:     BinaryOperator <=
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i <= j;

  // CHECK-NEXT:     BinaryOperator >=
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i >= j;

  // CHECK-NEXT:     BinaryOperator ==
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i == j;

  // CHECK-NEXT:     BinaryOperator !=
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i != j;

  // CHECK-NEXT:     BinaryOperator &
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i & j;

  // CHECK-NEXT:     BinaryOperator ^
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i ^ j;

  // CHECK-NEXT:     BinaryOperator |
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i | j;

  // CHECK-NEXT:     BinaryOperator &&
  // CHECK-NEXT:       ImplicitCastExpr IntegralToBoolean
  // CHECK-NEXT:         ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr IntegralToBoolean
  // CHECK-NEXT:         ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName j
  i && j;

  // CHECK-NEXT:     BinaryOperator ||
  // CHECK-NEXT:       ImplicitCastExpr IntegralToBoolean
  // CHECK-NEXT:         ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr IntegralToBoolean
  // CHECK-NEXT:         ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:           DeclRefExpr
  // CHECK-NEXT:             DeclarationName j
  i || j;

  // CHECK-NEXT:     BinaryOperator =
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i = j;

  // CHECK-NEXT:     CompoundAssignOperator *=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i *= j;

  // CHECK-NEXT:     CompoundAssignOperator /=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i /= j;

  // CHECK-NEXT:     CompoundAssignOperator %=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i %= j;

  // CHECK-NEXT:     CompoundAssignOperator +=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i += j;

  // CHECK-NEXT:     CompoundAssignOperator -=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i -= j;

  // CHECK-NEXT:     CompoundAssignOperator <<=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i <<= j;

  // CHECK-NEXT:     CompoundAssignOperator >>=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i >>= j;

  // CHECK-NEXT:     CompoundAssignOperator &=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i &= j;

  // CHECK-NEXT:     CompoundAssignOperator ^=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i ^= j;

  // CHECK-NEXT:     CompoundAssignOperator |=
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       ImplicitCastExpr LValueToRValue
  // CHECK-NEXT:         DeclRefExpr
  // CHECK-NEXT:           DeclarationName j
  i |= j;

  // CHECK-NEXT:     BinaryOperator ,
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName i
  // CHECK-NEXT:       DeclRefExpr
  // CHECK-NEXT:         DeclarationName j
  i , j;
}
