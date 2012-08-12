// RUN: ast -f Bool "%s" 2>&1 | FileCheck %s

class test1 {

  // CHECK: CXXConversionDecl
  // CHECK-NEXT:   DeclarationName operator _Bool
  // CHECK-NEXT:     BuiltinType bool
  // CHECK-NEXT:   FunctionProtoType
  // CHECK-NEXT:     BuiltinType bool
  operator bool();
};

// CHECK: CXXConversionDecl
// CHECK-NEXT:   NestedNameSpecifier test1::
// CHECK-NEXT:     RecordType
// CHECK-NEXT:   DeclarationName operator _Bool
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:   FunctionProtoType
// CHECK-NEXT:     BuiltinType bool
// CHECK-NEXT:   CompoundStmt
// CHECK-NEXT:     ReturnStmt
// CHECK-NEXT:       CXXBoolLiteralExpr false
test1::operator bool() { return false; }

class test2 {
  // CHECK: CXXConversionDecl
  // CHECK-NEXT:   DeclarationName operator _Bool
  // CHECK-NEXT:     BuiltinType bool
  // CHECK-NEXT:   FunctionProtoType
  // CHECK-NEXT:     BuiltinType bool
  // CHECK-NEXT:   CompoundStmt
  // CHECK-NEXT:     ReturnStmt
  // CHECK-NEXT:       CXXBoolLiteralExpr false
  operator bool() { return false; }
};

