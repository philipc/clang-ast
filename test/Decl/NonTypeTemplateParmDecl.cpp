// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: NonTypeTemplateParmDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType int
template<int test1> void f();
