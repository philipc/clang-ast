// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: UnresolvedUsingTypenameDecl
// CHECK-NEXT:   DeclarationName foo
// CHECK-NEXT:   NestedNameSpecifier Base<T>::
class Foo {
};
template <class T> class Base {
public:
	Foo foo;
};
template <class T> class test1 : public Base<T> {
	using typename Base<T>::foo;
};
