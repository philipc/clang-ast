// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   IncompleteArrayType
// CHECK-NEXT:     BuiltinType char
// CHECK-NEXT:   StringLiteral "val"
const char test1[] = "val";
