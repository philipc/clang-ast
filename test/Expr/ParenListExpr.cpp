// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:     CompoundStmt
// CHECK-NEXT:       CXXUnresolvedConstructExpr
// CHECK-NEXT:         TemplateTypeParmType
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template<typename T> void test1() { T(); };

// CHECK-NEXT: FunctionTemplateDecl
// CHECK-NEXT:   FunctionDecl
// CHECK-NEXT:     DeclarationName test2
// CHECK-NEXT:     FunctionProtoType
// CHECK-NEXT:       BuiltinType void
// CHECK-NEXT:     CompoundStmt
// CHECK-NEXT:       CXXUnresolvedConstructExpr
// CHECK-NEXT:         TemplateTypeParmType
// CHECK-NEXT:         IntegerLiteral 0
// CHECK-NEXT:         IntegerLiteral 1
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template<typename T> void test2() { T(0, 1); };
