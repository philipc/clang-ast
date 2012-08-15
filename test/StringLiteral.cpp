// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: VarDecl
// CHECK-NEXT:   Identifier test1
// CHECK-NEXT:   PointerType
// CHECK-NEXT:     BuiltinType char
// CHECK-NEXT:   ImplicitCastExpr
// CHECK-NEXT:     StringLiteral "val"
const char *test1 = "val";
