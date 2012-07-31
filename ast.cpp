#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#if 0
#include "clang/Tooling/CommandLineClangTool.h"
#endif
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::tooling;

class ASTPrinter : public ASTConsumer, public RecursiveASTVisitor<ASTPrinter> {
public:
  typedef RecursiveASTVisitor<ASTPrinter> VisitorBase;

  explicit ASTPrinter(
      raw_ostream &OS, const SourceManager &SM, const LangOptions& LO)
    : OS(OS), SM(SM), PP(LO), Indent(0), LastLocFilename(""), LastLocLine(~0U)
  {}

  virtual bool HandleTopLevelDecl(DeclGroupRef D) {
    for (DeclGroupRef::iterator I = D.begin(), E = D.end(); I != E; ++I) {
      TraverseDecl(*I);
    }
    OS << '\n';
    return true;
  }

  bool TraverseDecl(Decl *D) {
    ++Indent;
    bool Result = VisitorBase::TraverseDecl(D);
    --Indent;
    return Result;
  }

  bool VisitDecl(Decl *D) {
    PrintIndent();
    OS << D->getDeclKindName();
    PrintSourceRange(D->getSourceRange());
    return true;
  }

  bool VisitNamedDecl(NamedDecl *D) {
    OS << ' ' << D->getNameAsString();
    return true;
  }

  bool TraverseStmt(Stmt *S) {
    ++Indent;
    bool Result = VisitorBase::TraverseStmt(S);
    --Indent;
    return Result;
  }

  bool VisitStmt(Stmt *S) {
    PrintIndent();
    OS << S->getStmtClassName();
    PrintSourceRange(S->getSourceRange());
    return true;
  }

  bool TraverseType(QualType T) {
    ++Indent;
    bool Result = VisitorBase::TraverseType(T);
    --Indent;
    return Result;
  }

  bool VisitType(Type *T) {
    ++Indent;
    PrintIndent();
    OS << T->getTypeClassName();
    --Indent;
    return true;
  }

  bool VisitBuiltinType(BuiltinType *T) {
    OS << ' ' << T->getName(PP);
    return true;
  }

  bool VisitTypeLoc(TypeLoc TL) {
    PrintSourceRange(TL.getSourceRange());
    return true;
  }

  bool VisitQualifiedTypeLoc(QualifiedTypeLoc TL) {
    PrintSourceRange(TL.getSourceRange());
    return true;
  }

  void PrintIndent() {
    // FIXME: assumes that Indent 1 only occurs at the start of a top level decl
    if (Indent > 1)
      OS << '\n';
    for (unsigned i = 1; i < Indent; ++i)
      OS << "  ";
  }

  void PrintLocation(SourceLocation Loc) {
    // Based on StmtDumper::DumpLocation
    SourceLocation SpellingLoc = SM.getSpellingLoc(Loc);
    PresumedLoc PLoc = SM.getPresumedLoc(SpellingLoc);
    if (!PLoc.isValid())
      return;

    const char *Filename = PLoc.getFilename();
    unsigned Line = PLoc.getLine();
    if (strcmp(LastLocFilename, Filename) != 0) {
      OS << Filename << ':' << Line;
    } else if (LastLocLine != Line) {
      OS << "line:" << Line;
    } else {
      OS << "col";
    }
    OS << ':' << PLoc.getColumn();
    LastLocFilename = Filename;
    LastLocLine = Line;
  }

  void PrintSourceRange(SourceRange R) {
    OS << " <";
    PrintLocation(R.getBegin());
    if (R.getBegin() != R.getEnd()) {
      OS << ", ";
      PrintLocation(R.getEnd());
    }
    OS << ">";
  }

private:
  raw_ostream &OS;
  const SourceManager &SM;
  PrintingPolicy PP;
  unsigned Indent;
  const char *LastLocFilename;
  unsigned LastLocLine;
};

class ASTPrinterAction : public ASTFrontendAction {
public:
  virtual ASTConsumer *CreateASTConsumer(
      CompilerInstance &CI, StringRef InFile) {
    return new ASTPrinter(llvm::outs(),
        CI.getSourceManager(), CI.getLangOpts());
  }
};

bool runTool(int argc, const char *argv[], FrontendAction *ToolAction) {
  std::vector<std::string> CommandLine;
  CommandLine.push_back(argv[0]);
  CommandLine.push_back("-fsyntax-only");
  for (int i = 1; i < argc; ++i)
    CommandLine.push_back(argv[i]);
  FileManager Files((FileSystemOptions()));
  ToolInvocation Invocation(CommandLine, ToolAction, &Files);
  return Invocation.run();
}

int main(int argc, const char *argv[]) {
#if 0
  CommandLineClangTool Tool;
  Tool.initialize(argc, argv);
  return Tool.run(newFrontendActionFactory<ASTPrinterAction>());
#else
  //runToolOnCode(new ASTPrinterAction, argv[1]);
  runTool(argc, argv, new ASTPrinterAction);
  return 0;
#endif
}
