#include "llvm/Support/CommandLine.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#if 0
#include "clang/Tooling/CommandLineClangTool.h"
#endif
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::tooling;
using namespace llvm;

class ASTPrinterOptions {
public:
  ASTPrinterOptions() : EnableLoc(false) {}

  bool EnableLoc;
};

class ASTPrinter : public ASTConsumer, public RecursiveASTVisitor<ASTPrinter> {
public:
  typedef RecursiveASTVisitor<ASTPrinter> VisitorBase;

  explicit ASTPrinter(
      raw_ostream &OS, const SourceManager &SM, const LangOptions &LO,
      const ASTPrinterOptions &Options)
    : OS(OS), SM(SM), PP(LO), Indent(0), NeedNewline(false),
      LastLocFilename(""), LastLocLine(~0U), Options(Options)
  {}

  virtual void HandleTranslationUnit(ASTContext &Context) {
    TraverseDecl(Context.getTranslationUnitDecl());
  }

  bool TraverseDecl(Decl *D) {
    ++Indent;
    bool Result = VisitorBase::TraverseDecl(D);
    --Indent;
    // Finish off the line now in case this was the top level.
    // Currently only Decl can appear at the top level.
    if (NeedNewline) {
      OS << '\n';
      NeedNewline = false;
    }
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
    if (NeedNewline)
      OS << '\n';
    for (unsigned i = 1; i < Indent; ++i)
      OS << "  ";
    NeedNewline = true;
  }

  void PrintLocation(SourceLocation Loc) {
    if (!Options.EnableLoc)
      return;

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
    if (!Options.EnableLoc)
      return;

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
  bool NeedNewline;
  const char *LastLocFilename;
  unsigned LastLocLine;
  const ASTPrinterOptions &Options;
};

class ASTPrinterAction : public ASTFrontendAction {
public:
  ASTPrinterAction(const ASTPrinterOptions &Options) : Options(Options) {}

  virtual ASTConsumer *CreateASTConsumer(
      CompilerInstance &CI, StringRef InFile) {
    return new ASTPrinter(llvm::outs(),
        CI.getSourceManager(), CI.getLangOpts(), Options);
  }

private:
  const ASTPrinterOptions &Options;
};

bool runTool(cl::list<std::string> Argv, FrontendAction *ToolAction) {
  std::vector<std::string> CommandLine;
  CommandLine.push_back("clang-tool");
  CommandLine.push_back("-fsyntax-only");
  for (int i = 0; i < Argv.size(); ++i)
    CommandLine.push_back(Argv[i]);
  FileManager Files((FileSystemOptions()));
  ToolInvocation Invocation(CommandLine, ToolAction, &Files);
  return Invocation.run();
}

cl::opt<bool> EnableLoc(
    "l",
    cl::desc("Enable source locations"),
    cl::Optional);

cl::list<std::string> Argv(
    cl::Positional,
    cl::desc("Compiler arguments"));

int main(int argc, const char *argv[]) {
#if 0
  CommandLineClangTool Tool;
  Tool.initialize(argc, argv);
  return Tool.run(newFrontendActionFactory<ASTPrinterAction>());
#else
  //runToolOnCode(new ASTPrinterAction, argv[1]);
  cl::ParseCommandLineOptions(argc, argv);
  ASTPrinterOptions Options;
  Options.EnableLoc = EnableLoc;
  runTool(Argv, new ASTPrinterAction(Options));
  return 0;
#endif
}
