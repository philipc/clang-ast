// RUN: ast -f test -i "%s" 2>&1 | FileCheck %s

// CHECK: CXXRecordDecl struct
// CHECK-NEXT:   DeclarationName test
// FIXME: why is there a second implicit CXXRecordDecl for struct test?
// CHECK-NEXT:   CXXRecordDecl struct
// CHECK-NEXT:     DeclarationName test
// CHECK-NEXT:   CXXRecordDecl struct
// CHECK-NEXT:     CXXRecordDecl struct
// CHECK-NEXT:       FieldDecl
// CHECK-NEXT:         DeclarationName b
// CHECK-NEXT:         BuiltinType bool
// CHECK-NEXT:     FieldDecl
// CHECK-NEXT:       ElaboratedType
// CHECK-NEXT:         RecordType <anon>
// CHECK-NEXT:     IndirectFieldDecl
// CHECK-NEXT:       FieldDeclRef <anon>
// CHECK-NEXT:       FieldDeclRef b
// CHECK-NEXT:   FieldDecl
// CHECK-NEXT:     ElaboratedType
// CHECK-NEXT:       RecordType <anon>
// CHECK-NEXT:   IndirectFieldDecl
// CHECK-NEXT:     FieldDeclRef <anon>
// CHECK-NEXT:     FieldDeclRef <anon>
// CHECK-NEXT:     FieldDeclRef b
struct test {
  struct {
    struct {
      bool b;
    };
  };
};
