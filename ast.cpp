#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Regex.h"
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

template<typename T>
class ASTFilter : public RecursiveASTVisitor<ASTFilter<T> > {
public:
  typedef RecursiveASTVisitor<ASTFilter> VisitorBase;

  ASTFilter(T &Visitor, StringRef FilterString)
    : Visitor(Visitor), Filter(NULL) {
      if (!FilterString.empty()) {
        std::string Error;
        Filter = new Regex(FilterString);
        if (!Filter->isValid(Error))
          llvm::report_fatal_error("malformed filter expression: "
              + FilterString + ": " + Error);
      }
    }

  ~ASTFilter() {
    delete Filter;
  }

  bool TraverseDecl(Decl *D) {
    if (!Filter || Filter->match(getName(D)))
      return Visitor.TraverseDecl(D);
    return VisitorBase::TraverseDecl(D);
  }

private:
  std::string getName(Decl *D) {
    if (isa<NamedDecl>(D))
      return cast<NamedDecl>(D)->getNameAsString();
    return "";
  }

  T &Visitor;
  llvm::Regex *Filter;
};

class ASTPrinterOptions {
public:
  ASTPrinterOptions() {}

  bool EnableLoc;
  std::string FilterString;
};

class ASTPrinter : public ASTConsumer, public RecursiveASTVisitor<ASTPrinter> {
public:
  typedef RecursiveASTVisitor<ASTPrinter> VisitorBase;

  explicit ASTPrinter(raw_ostream &OS, const ASTPrinterOptions &Options)
    : Filter(*this, Options.FilterString), Context(NULL), OS(OS),
      Indent(0), NeedNewline(false),
      LastLocFilename(""), LastLocLine(~0U), Options(Options)
  {}

  virtual void HandleTranslationUnit(ASTContext &Context) {
    this->Context = &Context;
    Filter.TraverseDecl(Context.getTranslationUnitDecl());
    this->Context = NULL;
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
    printIndent();
    OS << D->getDeclKindName() << "Decl";
    printSourceRange(D->getSourceRange());
    // TODO: Attr
    return true;
  }

  bool VisitNamedDecl(NamedDecl *D) {
    OS << ' ' << D->getNameAsString();
    return true;
  }

  bool VisitVarDecl(VarDecl *D) {
    StorageClass SC = D->getStorageClassAsWritten();
    if (SC != SC_None)
      OS << ' ' << VarDecl::getStorageClassSpecifierString(SC);
    if (D->isThreadSpecified())
      OS << " __thread";
    if (D->isModulePrivate())
      OS << " __module_private__";
    // FIXME: incomplete
    return true;
  }

  bool TraverseStmt(Stmt *S) {
    ++Indent;
    bool Result = VisitorBase::TraverseStmt(S);
    --Indent;
    return Result;
  }

  bool VisitStmt(Stmt *S) {
    printIndent();
    OS << S->getStmtClassName();
    printSourceRange(S->getSourceRange());
    return true;
  }

  bool VisitLabelStmt(LabelStmt *S) {
    OS << ' ' << S->getDecl()->getNameAsString();
    return true;
  }

  bool VisitGotoStmt(GotoStmt *S) {
    OS << ' ' << S->getLabel()->getNameAsString();
    return true;
  }

  bool VisitIntegerLiteral(IntegerLiteral *E) {
    bool isSigned = E->getType()->isSignedIntegerType();
    OS << ' ' << E->getValue().toString(10, isSigned);
    return true;
  }

  bool VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *E) {
    OS << ' ' << (E->getValue() ? "true" : "false");
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
    printIndent();
    OS << T->getTypeClassName();
    --Indent;
    return true;
  }

  bool VisitBuiltinType(BuiltinType *T) {
    OS << ' ' << T->getName(Context->getPrintingPolicy());
    return true;
  }

  bool VisitTypeLoc(TypeLoc TL) {
    printSourceRange(TL.getSourceRange());
    return true;
  }

  bool VisitQualifiedTypeLoc(QualifiedTypeLoc TL) {
    printSourceRange(TL.getSourceRange());
    return true;
  }

private:
  void printIndent() {
    if (NeedNewline)
      OS << '\n';
    for (unsigned i = 1; i < Indent; ++i)
      OS << "  ";
    NeedNewline = true;
  }

  void printLocation(SourceLocation Loc, bool PrintLine) {
    if (!Options.EnableLoc)
      return;

    // Based on StmtDumper::DumpLocation
    SourceLocation SpellingLoc = Context->getSourceManager().getSpellingLoc(Loc);
    PresumedLoc PLoc = Context->getSourceManager().getPresumedLoc(SpellingLoc);
    if (!PLoc.isValid())
      return;

    const char *Filename = PLoc.getFilename();
    unsigned Line = PLoc.getLine();
    if (strcmp(LastLocFilename, Filename) != 0) {
      OS << Filename << ':';
      PrintLine = true;
    }
    if (PrintLine || LastLocLine != Line) {
      OS << Line << ':';
    }
    OS << PLoc.getColumn();
    LastLocFilename = Filename;
    LastLocLine = Line;
  }

  void printSourceRange(SourceRange R) {
    if (!Options.EnableLoc)
      return;

    OS << " <";
    printLocation(R.getBegin(), true);
    if (R.getBegin() != R.getEnd()) {
      OS << "-";
      printLocation(R.getEnd(), false);
    }
    OS << ">";
  }

  ASTFilter<ASTPrinter> Filter;
  ASTContext *Context;
  raw_ostream &OS;
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
    return new ASTPrinter(llvm::outs(), Options);
  }

private:
  const ASTPrinterOptions &Options;
};

bool runTool(cl::list<std::string> Argv, FrontendAction *ToolAction) {
  std::vector<std::string> CommandLine;
  CommandLine.push_back("clang-tool");
  CommandLine.push_back("-fsyntax-only");
  for (unsigned i = 0; i < Argv.size(); ++i)
    CommandLine.push_back(Argv[i]);
  FileManager Files((FileSystemOptions()));
  ToolInvocation Invocation(CommandLine, ToolAction, &Files);
  return Invocation.run();
}

cl::opt<bool> EnableLoc(
    "l",
    cl::desc("Enable source locations"),
    cl::Optional);

cl::opt<std::string> FilterString(
    "f",
    cl::desc("Filter named declarations"),
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
  Options.FilterString = FilterString;
  runTool(Argv, new ASTPrinterAction(Options));
  return 0;
#endif
}
