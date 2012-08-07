// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl test1
// CHECK-NEXT:   Builtin int
int test1;

// CHECK: VarDecl test2
// CHECK-NEXT:   Builtin int
// CHECK-NEXT:   IntegerLiteral 0
int test2 = 0;

// CHECK: VarDecl test3 extern
// CHECK-NEXT:   Builtin int
extern int test3;

// CHECK: VarDecl test4 static
// CHECK-NEXT:   Builtin int
static int test4;

// CHECK: VarDecl test5 __thread
// CHECK-NEXT:   Builtin int
__thread int test5;

// CHECK: VarDecl test6 __module_private__
// CHECK-NEXT:   Builtin int
__module_private__ int test6;
