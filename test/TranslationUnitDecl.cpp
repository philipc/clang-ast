// RUN: ast "%s" 2>&1 | FileCheck %s

int i;
int j;

// CHECK: TranslationUnitDecl
// CHECK-NEXT:   TypedefDecl
// CHECK-NEXT:     PointerType
// CHECK-NEXT:       BuiltinType char
// CHECK-NEXT:   VarDecl
// CHECK-NEXT:     Identifier i
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:   VarDecl
// CHECK-NEXT:     Identifier j
// CHECK-NEXT:     BuiltinType int
