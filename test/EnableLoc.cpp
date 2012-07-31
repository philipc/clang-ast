// RUN: ast -l "%s" 2>&1 | FileCheck %s

namespace test_namespace {

class TheClass {
public:
  int theMethod(int x) {
    return x + x;
  }
};

}

// CHECK: Namespace <{{.*}}:3:1, line:12:1> test_namespace
// CHECK-NEXT:   CXXRecord <line:5:1, line:10:1> TheClass
// CHECK-NEXT:     AccessSpec <line:6:1, col:7>
// CHECK-NEXT:     CXXMethod <line:7:3, line:9:3> theMethod
// CHECK-NEXT:       FunctionProto <line:7:3, col:22>
// CHECK-NEXT:       Builtin int <col:3>
// CHECK-NEXT:       ParmVar <col:17, col:21> x
// CHECK-NEXT:         Builtin int <col:17>
// CHECK-NEXT:       CompoundStmt <col:24, line:9:3>
// CHECK-NEXT:         ReturnStmt <line:8:5, col:16>
// CHECK-NEXT:           BinaryOperator <col:12, col:16>
// CHECK-NEXT:             ImplicitCastExpr <col:12>
// CHECK-NEXT:               DeclRefExpr <col:12>
// CHECK-NEXT:             ImplicitCastExpr <col:16>
// CHECK-NEXT:               DeclRefExpr <col:16>
