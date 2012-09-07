// RUN: ast -f test -- -std=c++11 "%s" 2>&1 | FileCheck %s

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   StaticAssertDecl
// CHECK-NEXT:     CXXBoolLiteralExpr true
// CHECK-NEXT:     StringLiteral "msg"
namespace test1 {
  static_assert(true, "msg");
};
