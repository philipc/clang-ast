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
      return cast<NamedDecl>(D)->getQualifiedNameAsString();
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

  explicit ASTPrinter(raw_ostream &OS, const ASTPrinterOptions &Options);
  virtual void HandleTranslationUnit(ASTContext &Context);

  bool TraverseDecl(Decl *D);
  bool VisitDecl(Decl *D);
  bool VisitVarDecl(VarDecl *D);
  bool VisitFunctionDecl(FunctionDecl *D);
  bool VisitLabelDecl(LabelDecl *D);

  bool TraverseStmt(Stmt *S);
  bool VisitStmt(Stmt *S);
  bool VisitLabelStmt(LabelStmt *S);
  bool VisitGotoStmt(GotoStmt *S);

  bool VisitPredefinedExpr(PredefinedExpr *E);
  bool VisitIntegerLiteral(IntegerLiteral *E);
  bool VisitFloatingLiteral(FloatingLiteral *E);
  bool VisitStringLiteral(StringLiteral *E);
  bool VisitCharacterLiteral(CharacterLiteral *E);
  bool VisitUnaryOperator(UnaryOperator *E);
  bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *E);
  bool VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *E);

  bool TraverseType(QualType T);
  bool VisitType(Type *T);
  bool VisitBuiltinType(BuiltinType *T);
  bool VisitRecordType(RecordType *T);

  bool TraverseTypeLoc(TypeLoc TL);
  bool VisitTypeLoc(TypeLoc TL);
  bool VisitQualifiedTypeLoc(QualifiedTypeLoc TL);

  bool TraverseNestedNameSpecifier(NestedNameSpecifier *NNS);
  bool TraverseNestedNameSpecifierLoc(NestedNameSpecifierLoc NNS);
  bool TraverseDeclarationNameInfo(DeclarationNameInfo NameInfo);
  bool TraverseConstructorInitializer(CXXCtorInitializer *Init);
  bool TraverseTemplateArgument(const TemplateArgument &Arg);
  bool TraverseTemplateArgumentLoc(const TemplateArgumentLoc &ArgLoc);

private:
  void printIndent();
  void printIdentifier(NamedDecl *D);
  void printLocation(SourceLocation Loc, bool PrintLine);
  void printLocation(SourceLocation Loc);
  void printSourceRange(SourceRange R);
  ASTFilter<ASTPrinter> Filter;
  ASTContext *Context;
  raw_ostream &OS;
  unsigned Indent;
  bool NeedNewline;
  const char *LastLocFilename;
  unsigned LastLocLine;
  const ASTPrinterOptions &Options;
};

ASTPrinter::ASTPrinter(raw_ostream &OS, const ASTPrinterOptions &Options)
  : Filter(*this, Options.FilterString), Context(NULL), OS(OS),
    Indent(0), NeedNewline(false),
    LastLocFilename(""), LastLocLine(~0U), Options(Options)
{}

void ASTPrinter::HandleTranslationUnit(ASTContext &Context) {
  this->Context = &Context;
  Filter.TraverseDecl(Context.getTranslationUnitDecl());
  this->Context = NULL;
}

bool ASTPrinter::TraverseDecl(Decl *D) {
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

bool ASTPrinter::VisitDecl(Decl *D) {
  printIndent();
  OS << D->getDeclKindName() << "Decl";
  printSourceRange(D->getSourceRange());
  // TODO: Attr
  return true;
}

bool ASTPrinter::VisitVarDecl(VarDecl *D) {
  StorageClass SC = D->getStorageClassAsWritten();
  if (SC != SC_None)
    OS << ' ' << VarDecl::getStorageClassSpecifierString(SC);
  if (D->isThreadSpecified())
    OS << " __thread";
  if (D->isModulePrivate())
    OS << " __module_private__";

  // TODO: more properties

  printIdentifier(D);
  return true;
}

bool ASTPrinter::VisitFunctionDecl(FunctionDecl *D) {
  StorageClass SC = D->getStorageClassAsWritten();
  if (SC != SC_None)
    OS << ' ' << VarDecl::getStorageClassSpecifierString(SC);
  if (D->isInlineSpecified())
    OS << " inline";
  if (D->isVirtualAsWritten())
    OS << " virtual";
  if (D->isModulePrivate())
    OS << " __module_private__";
  // TODO: more properties
  return true;
}

bool ASTPrinter::VisitLabelDecl(LabelDecl *D) {
  printIdentifier(D);
  return true;
}

bool ASTPrinter::TraverseStmt(Stmt *S) {
  ++Indent;
  bool Result = VisitorBase::TraverseStmt(S);
  --Indent;
  return Result;
}

bool ASTPrinter::VisitStmt(Stmt *S) {
  printIndent();
  OS << S->getStmtClassName();
  printSourceRange(S->getSourceRange());
  return true;
}

bool ASTPrinter::VisitLabelStmt(LabelStmt *S) {
  printIdentifier(S->getDecl());
  return true;
}

bool ASTPrinter::VisitGotoStmt(GotoStmt *S) {
  printIdentifier(S->getLabel());
  return true;
}

bool ASTPrinter::VisitPredefinedExpr(PredefinedExpr *E) {
  switch (E->getIdentType()) {
  default:
    llvm_unreachable("unknown IdentType");
  case PredefinedExpr::Func:
    OS << " __func__";
    break;
  case PredefinedExpr::Function:
    OS << " __FUNCTION__";
    break;
  case PredefinedExpr::LFunction:
    OS << " L__FUNCTION__";
    break;
  case PredefinedExpr::PrettyFunction:
    OS << " __PRETTY_FUNCTION__";
    break;
  }
  return true;
}

bool ASTPrinter::VisitIntegerLiteral(IntegerLiteral *E) {
  bool isSigned = E->getType()->isSignedIntegerType();
  OS << ' ' << E->getValue().toString(10, isSigned);
  return true;
}

bool ASTPrinter::VisitFloatingLiteral(FloatingLiteral *E) {
  OS << ' ' << E->getValueAsApproximateDouble();
  return true;
}

bool ASTPrinter::VisitStringLiteral(StringLiteral *E) {
  OS << ' ';
  E->outputString(OS);
  return true;
}

bool ASTPrinter::VisitCharacterLiteral(CharacterLiteral *E) {
  OS << ' ' << E->getValue();
  return true;
}

bool ASTPrinter::VisitUnaryOperator(UnaryOperator *E) {
  OS << ' ' << (E->isPostfix() ? "postfix" : "prefix")
     << ' ' << UnaryOperator::getOpcodeStr(E->getOpcode());
  return true;
}

bool ASTPrinter::VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *E) {
  switch (E->getKind()) {
  default:
    llvm_unreachable("unknown IdentType");
  case UETT_SizeOf:
    OS << " sizeof";
    break;
  case UETT_AlignOf:
    OS << " alignof";
    break;
  case UETT_VecStep:
    OS << " vec_step";
    break;
  }
  return true;
}

bool ASTPrinter::VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *E) {
  OS << ' ' << (E->getValue() ? "true" : "false");
  return true;
}

bool ASTPrinter::TraverseType(QualType T) {
  ++Indent;
  bool Result = VisitorBase::TraverseType(T);
  --Indent;
  return Result;
}

bool ASTPrinter::VisitType(Type *T) {
  printIndent();
  OS << T->getTypeClassName() << "Type";
  return true;
}

bool ASTPrinter::VisitBuiltinType(BuiltinType *T) {
  OS << ' ' << T->getName(Context->getPrintingPolicy());
  return true;
}

bool ASTPrinter::VisitRecordType(RecordType *T) {
  printIdentifier(T->getDecl());
  return true;
}

bool ASTPrinter::TraverseTypeLoc(TypeLoc TL) {
  ++Indent;
  bool Result = VisitorBase::TraverseTypeLoc(TL);
  --Indent;
  return Result;
}

bool ASTPrinter::VisitTypeLoc(TypeLoc TL) {
  printSourceRange(TL.getSourceRange());
  return true;
}

bool ASTPrinter::VisitQualifiedTypeLoc(QualifiedTypeLoc TL) {
  printSourceRange(TL.getSourceRange());
  return true;
}

bool ASTPrinter::TraverseNestedNameSpecifier(NestedNameSpecifier *NNS) {
  if (!NNS)
    return true;

  ++Indent;
  printIndent();
  OS << "NestedNameSpecifier ";
  NNS->print(OS, Context->getPrintingPolicy());
  bool Result = VisitorBase::TraverseNestedNameSpecifier(NNS);
  --Indent;
  return Result;
}

bool ASTPrinter::TraverseNestedNameSpecifierLoc(NestedNameSpecifierLoc NNS) {
  if (!NNS)
    return true;

  ++Indent;
  printIndent();
  OS << "NestedNameSpecifier";
  printSourceRange(NNS.getSourceRange());
  OS << ' ';
  NNS.getNestedNameSpecifier()->print(OS, Context->getPrintingPolicy());
  bool Result = VisitorBase::TraverseNestedNameSpecifierLoc(NNS);
  --Indent;
  return Result;
}

bool ASTPrinter::TraverseDeclarationNameInfo(DeclarationNameInfo NameInfo) {
  ++Indent;
  printIndent();
  OS << "DeclarationName";
  printSourceRange(NameInfo.getSourceRange());
  OS << ' ';
  NameInfo.getName().printName(OS);
  bool Result = VisitorBase::TraverseDeclarationNameInfo(NameInfo);
  --Indent;
  return Result;
}

bool ASTPrinter::TraverseConstructorInitializer(CXXCtorInitializer *Init) {
  ++Indent;
  printIndent();
  OS << "CXXCtorInitializer ";
  printSourceRange(Init->getSourceRange());
  if (Init->isBaseInitializer())
    TraverseTypeLoc(Init->getTypeSourceInfo()->getTypeLoc());
  else if (Init->isAnyMemberInitializer())
    printIdentifier(Init->getAnyMember());
  if (Init->isWritten())
    TraverseStmt(Init->getInit());
  --Indent;
  return true;
}

bool ASTPrinter::TraverseTemplateArgument(const TemplateArgument &Arg) {
  ++Indent;
  printIndent();
  OS << "TemplateArgument";
  bool Result = VisitorBase::TraverseTemplateArgument(Arg);
  --Indent;
  return Result;
}

bool ASTPrinter::TraverseTemplateArgumentLoc(const TemplateArgumentLoc &ArgLoc) {
  ++Indent;
  printIndent();
  OS << "TemplateArgument";
  printSourceRange(ArgLoc.getSourceRange());
  bool Result = VisitorBase::TraverseTemplateArgumentLoc(ArgLoc);
  --Indent;
  return Result;
}

void ASTPrinter::printIndent() {
  if (NeedNewline)
    OS << '\n';
  for (unsigned i = 1; i < Indent; ++i)
    OS << "  ";
  NeedNewline = true;
}

void ASTPrinter::printIdentifier(NamedDecl *D) {
  ++Indent;
  printIndent();
  OS << "Identifier";
  printLocation(D->getLocation());
  OS << ' ' << D->getNameAsString();
  --Indent;
}

void ASTPrinter::printLocation(SourceLocation Loc, bool PrintLine) {
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

void ASTPrinter::printLocation(SourceLocation Loc) {
  if (!Options.EnableLoc)
    return;

  OS << " <";
  printLocation(Loc, true);
  OS << ">";
}

void ASTPrinter::printSourceRange(SourceRange R) {
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
