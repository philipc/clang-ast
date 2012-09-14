// RUN: ast -i -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType int
int test1;

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test2
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 0
int test2 = 0;

// CHECK: VarDecl extern
// CHECK-NEXT:   DeclarationName test3
// CHECK-NEXT:   BuiltinType int
extern int test3;

// CHECK: VarDecl static
// CHECK-NEXT:   DeclarationName test4
// CHECK-NEXT:   BuiltinType int
static int test4;

// CHECK: VarDecl __thread
// CHECK-NEXT:   DeclarationName test5
// CHECK-NEXT:   BuiltinType int
__thread int test5;

// CHECK: VarDecl __module_private__
// CHECK-NEXT:   DeclarationName test6
// CHECK-NEXT:   BuiltinType int
__module_private__ int test6;

namespace A {
// CHECK: VarDecl extern
// CHECK-NEXT:   DeclarationName test7
// CHECK-NEXT:   BuiltinType int
  extern int test7;

// CHECK: VarDecl extern
// CHECK-NEXT:   DeclarationName test8
// CHECK-NEXT:   BuiltinType int
  extern int test8;
};

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test7
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   BuiltinType int
int A::test7;

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test8
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 0
int A::test8 = 0;

// CHECK-NEXT: FunctionDecl
// CHECK-NEXT:   DeclarationName test9
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType void
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     DeclStmt
// CHECK-NEXT:       VarDecl
// CHECK-NEXT:         ElaboratedType
// CHECK-NEXT:           RecordType <anon>
// CHECK-NEXT:         CXXConstructExpr
// FIXME: the VarDecl shouldn't be implicit
// FIXME: should traverse the RecordDecl too
void test9() {
  union { int i; };
}
