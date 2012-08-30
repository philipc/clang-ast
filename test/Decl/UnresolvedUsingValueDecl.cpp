// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: UnresolvedUsingValueDecl
// CHECK-NEXT:   NestedNameSpecifier Base<T>::
// CHECK-NEXT:     TemplateSpecializationType
// CHECK-NEXT:       TemplateArgument
// CHECK-NEXT:         TemplateTypeParmType
// CHECK-NEXT:   DeclarationName foo
class Foo {
};
template <class T> class Base {
public:
	Foo foo;
};
template <class T> class test1 : public Base<T> {
	using Base<T>::foo;
};
