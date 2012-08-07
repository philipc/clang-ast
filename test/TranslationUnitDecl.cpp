// RUN: ast "%s" 2>&1 | FileCheck %s

int i;
int j;

// CHECK: TranslationUnitDecl
// CHECK-NEXT:   TypedefDecl __builtin_va_list
// CHECK-NEXT:     Pointer
// CHECK-NEXT:     Builtin char
// CHECK-NEXT:   VarDecl i
// CHECK-NEXT:     Builtin int
// CHECK-NEXT:   VarDecl j
// CHECK-NEXT:     Builtin int
