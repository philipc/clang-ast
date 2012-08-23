// RUN: ast "%s" 2>&1 | FileCheck %s

int i;
int j;

// CHECK: TranslationUnitDecl
// CHECK-NEXT:   TypedefDecl
// CHECK-NEXT:     DeclarationName __builtin_va_list
// CHECK-NEXT:     PointerType
// CHECK-NEXT:       BuiltinType char
// CHECK-NEXT:   VarDecl
// CHECK-NEXT:     DeclarationName i
// CHECK-NEXT:     BuiltinType int
// CHECK-NEXT:   VarDecl
// CHECK-NEXT:     DeclarationName j
// CHECK-NEXT:     BuiltinType int
