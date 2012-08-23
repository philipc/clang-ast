// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: TypeAliasDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType bool
using test1 = bool;
