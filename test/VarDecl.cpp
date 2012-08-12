// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test1
// CHECK-NEXT:   BuiltinType int
int test1;

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test2
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 0
int test2 = 0;

// CHECK: VarDecl extern
// CHECK-NEXT:   Identifier test3
// CHECK-NEXT:   BuiltinType int
extern int test3;

// CHECK: VarDecl static
// CHECK-NEXT:   Identifier test4
// CHECK-NEXT:   BuiltinType int
static int test4;

// CHECK: VarDecl __thread
// CHECK-NEXT:   Identifier test5
// CHECK-NEXT:   BuiltinType int
__thread int test5;

// CHECK: VarDecl __module_private__
// CHECK-NEXT:   Identifier test6
// CHECK-NEXT:   BuiltinType int
__module_private__ int test6;

namespace A {
// CHECK: VarDecl extern
// CHECK-NEXT:   Identifier test7
// CHECK-NEXT:   BuiltinType int
  extern int test7;

// CHECK: VarDecl extern
// CHECK-NEXT:   Identifier test8
// CHECK-NEXT:   BuiltinType int
  extern int test8;
};

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test7
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   BuiltinType int
int A::test7;

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test8
// CHECK-NEXT:   NestedNameSpecifier A::
// CHECK-NEXT:   BuiltinType int
// CHECK-NEXT:   IntegerLiteral 0
int A::test8 = 0;
