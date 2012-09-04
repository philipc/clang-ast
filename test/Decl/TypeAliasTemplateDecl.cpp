// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: TypeAliasTemplateDecl
// CHECK-NEXT:   TypeAliasDecl
// CHECK-NEXT:     DeclarationName test1
// CHECK-NEXT:     TemplateTypeParmType
// CHECK-NEXT:   TemplateTypeParmDecl
// CHECK-NEXT:     DeclarationName T
template<typename T> using test1 = T;
