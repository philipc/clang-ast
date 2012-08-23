// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: TypedefDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType bool
typedef bool test1;
