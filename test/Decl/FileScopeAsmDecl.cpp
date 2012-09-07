// RUN: ast -f test "%s" 2>&1 | FileCheck %s

// CHECK: NamespaceDecl
// CHECK-NEXT:   DeclarationName test1
// CHECK-NEXT:   FileScopeAsmDecl
// CHECK-NEXT:     StringLiteral "ret"
namespace test1 {
  asm("ret");
}
