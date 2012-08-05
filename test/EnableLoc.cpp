// RUN: ast -l "%s" 2>&1 | FileCheck %s

namespace test_namespace {

class TheClass {
public:
  int theMethod(int x) {
    return x + x;
  }
};

}

// CHECK: Namespace <{{.*}}:3:1-12:1> test_namespace
// CHECK-NEXT:   CXXRecord <5:1-10:1> TheClass
// CHECK-NEXT:     AccessSpec <6:1-7>
// CHECK-NEXT:     CXXMethod <7:3-9:3> theMethod
// CHECK-NEXT:       FunctionProto <7:3-22>
// CHECK-NEXT:       Builtin int <7:3>
// CHECK-NEXT:       ParmVar <7:17-21> x
// CHECK-NEXT:         Builtin int <7:17>
// CHECK-NEXT:       CompoundStmt <7:24-9:3>
// CHECK-NEXT:         ReturnStmt <8:5-16>
// CHECK-NEXT:           BinaryOperator <8:12-16>
// CHECK-NEXT:             ImplicitCastExpr <8:12>
// CHECK-NEXT:               DeclRefExpr <8:12>
// CHECK-NEXT:             ImplicitCastExpr <8:16>
// CHECK-NEXT:               DeclRefExpr <8:16>
