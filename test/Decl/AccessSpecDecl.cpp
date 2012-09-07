// RUN: ast -f test -- "%s" 2>&1 | FileCheck %s

// CHECK: CXXRecordDecl class
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   AccessSpecDecl public
// CHECK-NEXT:   AccessSpecDecl protected
// CHECK-NEXT:   AccessSpecDecl private
class test1 {
public:
protected:
private:
};
