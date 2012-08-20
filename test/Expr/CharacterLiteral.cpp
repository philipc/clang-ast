// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   BuiltinType char
// CHECK-NEXT:   CharacterLiteral 97
char test1 = 'a';
