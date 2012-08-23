// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: EnumDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   EnumType
enum test1;
