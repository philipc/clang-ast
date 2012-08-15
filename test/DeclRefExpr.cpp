// RUN: ast -f test -- -Wno-unused-value "%s" 2>&1 | FileCheck %s

int i;
namespace A {
  template<typename T> T f();
};

// CHECK:   CompoundStmt
// CHECK-NEXT:     DeclRefExpr
// CHECK-NEXT:       DeclarationName i
// CHECK-NEXT:     DeclRefExpr
// CHECK-NEXT:       NestedNameSpecifier A::
// CHECK-NEXT:       DeclarationName f
// CHECK-NEXT:       TemplateArgument
// CHECK-NEXT:         BuiltinType bool
void test() {
  i;
  A::f<bool>;
};
