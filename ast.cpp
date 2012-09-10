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
  bool EnableImplicit;
  std::string FilterString;
};

class ASTPrinter : public ASTConsumer, public RecursiveASTVisitor<ASTPrinter> {
public:
  typedef RecursiveASTVisitor<ASTPrinter> VisitorBase;

  explicit ASTPrinter(raw_ostream &OS, const ASTPrinterOptions &Options);
  virtual void HandleTranslationUnit(ASTContext &Context);

  bool shouldVisitImplicitCode() { return Options.EnableImplicit; }
  bool shouldVisitTemplateInstantiations() { return Options.EnableImplicit; }

  bool TraverseDecl(Decl *D);
  bool VisitDecl(Decl *D);
  // TranslationUnitDecl empty
  bool VisitNamedDecl(NamedDecl *D);
  bool VisitNamespaceDecl(NamespaceDecl *D);
  bool VisitUsingDirectiveDecl(UsingDirectiveDecl *D);
  bool VisitNamespaceAliasDecl(NamespaceAliasDecl *D);
  bool VisitLabelDecl(LabelDecl *D);
  bool VisitTypeDecl(TypeDecl *D);
  bool VisitTypedefNameDecl(TypedefNameDecl *D);
  // TypedefDecl empty
  // TypeAliasDecl empty
  bool VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *D);
  bool VisitTagDecl(TagDecl *D);
  bool VisitEnumDecl(EnumDecl *D);
  bool VisitRecordDecl(RecordDecl *D);
  bool VisitCXXRecordDecl(CXXRecordDecl *D);
  bool TraverseClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D);
  bool VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D);
  bool VisitClassTemplatePartialSpecializationDecl(ClassTemplatePartialSpecializationDecl *D);
  bool VisitTemplateTypeParmDecl(TemplateTypeParmDecl *D);
  // ValueDecl empty
  bool VisitEnumConstantDecl(EnumConstantDecl *D);
  // UnresolvedUsingValueDecl empty
  bool TraverseIndirectFieldDecl(IndirectFieldDecl *D);
  // IndirectFieldDecl empty
  // DeclaratorDecl empty
  bool VisitFunctionDecl(FunctionDecl *D);
  bool VisitCXXMethodDecl(CXXMethodDecl *D);
  bool VisitCXXConstructorDecl(CXXConstructorDecl *D);
  bool VisitCXXDestructorDecl(CXXDestructorDecl *D);
  bool VisitCXXConversionDecl(CXXConversionDecl *D);
  bool VisitFieldDecl(FieldDecl *D);
  // TODO: ObjCIvarDecl
  // TODO: ObjCAtDefsFieldDecl
  bool VisitVarDecl(VarDecl *D);
  // ImplicitParamDecl empty
  // TODO: test ImplicitParamDecl (ObjC only?)
  bool VisitParmVarDecl(ParmVarDecl *D);
  bool VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *D);
  // TemplateDecl empty
  bool VisitRedeclarableTemplateDecl(RedeclarableTemplateDecl *D);
  // FunctionTemplateDecl empty
  // ClassTemplateDecl empty
  // TypeAliasTemplateDecl empty
  bool VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *D);
  bool VisitUsingDecl(UsingDecl *D);
  bool VisitUsingShadowDecl(UsingShadowDecl *D);
  // TODO: ObjCMethodDecl
  // TODO: ObjCContainerDecl
  // TODO: ObjCCategoryDecl
  // TODO: ObjCProtocolDecl
  // TODO: ObjCInterfaceDecl
  // TODO: ObjCImplDecl
  // TODO: ObjCCategoryImplDecl
  // TODO: ObjCImplementationDecl
  // TODO: ObjCPropertyDecl
  // TODO: ObjCCompatibleAliasDecl
  bool VisitLinkageSpecDecl(LinkageSpecDecl *D);
  // TODO: ObjCPropertyImplDecl
  // FileScopeAsmDecl empty
  bool VisitAccessSpecDecl(AccessSpecDecl *D);
  bool VisitFriendDecl(FriendDecl *D);
  // TODO: FriendTemplateDecl
  // TODO: StaticAssertDecl->isFailed()

  // Extensions
  // TODO: BlockDecl
  // TODO: ClassScopeFunctionSpecializationDecl
  // TODO: ImportDecl

  // Statements
  bool TraverseStmt(Stmt *S);
  bool VisitStmt(Stmt *S);
  bool VisitNullStmt(NullStmt *S);
  // CompoundStmt empty
  bool VisitLabelStmt(LabelStmt *S);
  bool VisitAttributedStmt(AttributedStmt *S);
  // IfStmt empty
  bool VisitSwitchStmt(SwitchStmt *S);
  // WhileStmt empty
  // DoStmt empty
  // ForStmt empty
  bool VisitGotoStmt(GotoStmt *S);
  // IndirectGotoStmt empty
  // ContinueStmt empty
  // BreakStmt empty
  bool VisitReturnStmt(ReturnStmt *S);
  // DeclStmt 
  // SwitchCase empty
  // CaseStmt empty
  // DefaultStmt empty
  // AsmStmt empty
  bool VisitGCCAsmStmt(GCCAsmStmt *S);
  // TODO: MSAsmStmt

  // Obj-C statements
  // TODO: ObjCAtTryStmt
  // TODO: ObjCAtCatchStmt
  // TODO: ObjCAtFinallyStmt
  // TODO: ObjCAtThrowStmt
  // TODO: ObjCAtSynchronizedStmt
  // TODO: ObjCForCollectionStmt
  // TODO: ObjCAutoreleasePoolStmt

  // C++ statments
  // CXXCatchStmt empty
  // CXXTryStmt empty
  // CXXForRangeStmt empty

  // Expressions
  bool VisitExpr(Expr *E);
  bool VisitPredefinedExpr(PredefinedExpr *E);
  bool VisitDeclRefExpr(DeclRefExpr *E);
  bool VisitIntegerLiteral(IntegerLiteral *E);
  bool VisitFloatingLiteral(FloatingLiteral *E);
  // ImaginaryLiteral empty
  bool VisitStringLiteral(StringLiteral *E);
  bool VisitCharacterLiteral(CharacterLiteral *E);
  // ParenExpr empty
  bool VisitUnaryOperator(UnaryOperator *E);
  bool VisitOffsetOfExpr(OffsetOfExpr *E);
  bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *E);
  // ArraySubscriptExpr empty
  // CallExpr empty
  bool VisitMemberExpr(MemberExpr *E);
  // TODO: CastExpr
  // TODO: BinaryOperator
  // TODO: CompoundAssignOperator
  // TODO: AbstractConditionalOperator
  // TODO: ConditionalOperator
  // TODO: BinaryConditionalOperator
  // TODO: ImplicitCastExpr
  // TODO: ExplicitCastExpr
  // TODO: CStyleCastExpr
  // TODO: CompoundLiteralExpr
  // TODO: ExtVectorElementExpr
  // TODO: InitListExpr
  // TODO: DesignatedInitExpr
  // TODO: ImplicitValueInitExpr
  // TODO: ParenListExpr
  // TODO: VAArgExpr
  // TODO: GenericSelectionExpr
  // TODO: PseudoObjectExpr

  // Atomic expressions
  // TODO: AtomicExpr

  // GNU Extensions.
  // TODO: AddrLabelExpr
  // TODO: StmtExpr
  // TODO: ChooseExpr
  // TODO: GNUNullExpr

  // C++ Expressions.
  // TODO: CXXOperatorCallExpr
  // TODO: CXXMemberCallExpr
  // TODO: CXXNamedCastExpr
  // TODO: CXXStaticCastExpr
  // TODO: CXXDynamicCastExpr
  // TODO: CXXReinterpretCastExpr
  // TODO: CXXConstCastExpr
  // TODO: CXXFunctionalCastExpr
  // TODO: CXXTypeidExpr
  // TODO: UserDefinedLiteral
  bool VisitCXXBoolLiteralExpr(CXXBoolLiteralExpr *E);
  // TODO: CXXNullPtrLiteralExpr
  // TODO: CXXThisExpr
  // TODO: CXXThrowExpr
  // TODO: CXXDefaultArgExpr
  // TODO: CXXScalarValueInitExpr
  // TODO: CXXNewExpr
  // TODO: CXXDeleteExpr
  // TODO: CXXPseudoDestructorExpr
  // TODO: TypeTraitExpr
  // TODO: UnaryTypeTraitExpr
  // TODO: BinaryTypeTraitExpr
  // TODO: ArrayTypeTraitExpr
  // TODO: ExpressionTraitExpr
  // TODO: DependentScopeDeclRefExpr
  // TODO: CXXConstructExpr
  // TODO: CXXBindTemporaryExpr
  // TODO: ExprWithCleanups
  // TODO: CXXTemporaryObjectExpr
  // TODO: CXXUnresolvedConstructExpr
  // TODO: CXXDependentScopeMemberExpr
  // TODO: OverloadExpr
  // TODO: UnresolvedLookupExpr
  // TODO: UnresolvedMemberExpr
  // TODO: CXXNoexceptExpr
  // TODO: PackExpansionExpr
  // TODO: SizeOfPackExpr
  // TODO: SubstNonTypeTemplateParmExpr
  // TODO: SubstNonTypeTemplateParmPackExpr
  // TODO: MaterializeTemporaryExpr
  // TODO: LambdaExpr

  // Obj-C Expressions.
  // TODO: ObjCStringLiteral
  // TODO: ObjCBoxedExpr
  // TODO: ObjCArrayLiteral
  // TODO: ObjCDictionaryLiteral
  // TODO: ObjCEncodeExpr
  // TODO: ObjCMessageExpr
  // TODO: ObjCSelectorExpr
  // TODO: ObjCProtocolExpr
  // TODO: ObjCIvarRefExpr
  // TODO: ObjCPropertyRefExpr
  // TODO: ObjCIsaExpr
  // TODO: ObjCIndirectCopyRestoreExpr
  // TODO: ObjCBoolLiteralExpr
  // TODO: ObjCSubscriptRefExpr

  // Obj-C ARC Expressions.
  // TODO: ObjCBridgedCastExpr

  // CUDA Expressions.
  // TODO: CUDAKernelCallExpr

  // Clang Extensions.
  // TODO: ShuffleVectorExpr
  // TODO: BlockExpr
  // TODO: OpaqueValueExpr

  // Microsoft Extensions.
  // TODO: CXXUuidofExpr
  // TODO: SEHTryStmt
  // TODO: SEHExceptStmt
  // TODO: SEHFinallyStmt
  // TODO: MSDependentExistsStmt

  // OpenCL Extensions.
  // TODO: AsTypeExpr

  bool TraverseType(QualType T);
  bool VisitType(Type *T);
  bool VisitBuiltinType(BuiltinType *T);
  bool VisitRecordType(RecordType *T);
  // TODO: Type

  // TODO: Attr

  bool TraverseTypeLoc(TypeLoc TL);
  bool VisitTypeLoc(TypeLoc TL);
  bool VisitQualifiedTypeLoc(QualifiedTypeLoc TL);

  bool TraverseNestedNameSpecifier(NestedNameSpecifier *NNS);
  bool TraverseNestedNameSpecifierLoc(NestedNameSpecifierLoc NNS);
  bool TraverseDeclarationNameInfo(DeclarationNameInfo NameInfo);
  bool TraverseTemplateArgument(const TemplateArgument &Arg);
  bool TraverseTemplateArgumentLoc(const TemplateArgumentLoc &ArgLoc);
  bool TraverseConstructorInitializer(CXXCtorInitializer *Init);

private:
  void printNewline();
  void printIndent();
  void printDeclRef(NamedDecl *D, SourceLocation Loc);
  void printIdentifier(NamedDecl *D);
  void printLocation(SourceLocation Loc, bool PrintLine);
  void printLocation(SourceLocation Loc);
  void printSourceRange(SourceRange R);

  ASTFilter<ASTPrinter> Filter;
  ASTContext *Context;
  raw_ostream &OS;
  unsigned Indent;
  bool NeedNewline;
  SourceRange NeedLoc;
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
  printNewline();
  return Result;
}

bool ASTPrinter::VisitDecl(Decl *D) {
  printIndent();
  OS << D->getDeclKindName() << "Decl";
  printSourceRange(D->getSourceRange());
  // TODO: getDeclContext()
  // TODO: getLexicalDeclContext()
  // TODO: isInvalidDecl()
  // TODO: getAttrs()
  // TODO: isImplicit()
  // TODO: isUsed()
  // TODO: isReferenced()
  // TODO: isTopLevelDeclInObjCContainer()
  // TODO: getAccess()
  // TODO: AccessSpecifier
  // TODO: various bool members

  // TODO: isModulePrivate() in all children
  // - can't here because it is protected
  return true;
}

bool ASTPrinter::VisitNamedDecl(NamedDecl *D) {
  if (D->isModulePrivate())
    OS << " __module_private__";

  // TODO: getDeclName() in all children
  // - can't here because some already traverse it
  return true;
}

bool ASTPrinter::VisitNamespaceDecl(NamespaceDecl *D) {
  // TODO: VisitRedeclarable()
  // TODO: isInline()
  // TODO: isOriginalNamespace()
  // TODO: getOriginalNamespace()

  // FIXME: move into RAV?
  if (!D->isAnonymousNamespace())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitUsingDirectiveDecl(UsingDirectiveDecl *D) {
  // getDeclName() is a dummy value
  // TODO: getCommonAncestor()

  printDeclRef(D->getNominatedNamespace(), D->getLocation());
  return true;
}

bool ASTPrinter::VisitNamespaceAliasDecl(NamespaceAliasDecl *D) {
  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  // FIXME: move into RAV?
  TraverseNestedNameSpecifierLoc(D->getQualifierLoc());
  printDeclRef(D->getNamespace(), D->getTargetNameLoc());
  return true;
}

bool ASTPrinter::VisitLabelDecl(LabelDecl *D) {
  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitTypeDecl(TypeDecl *D) {
  return true;
}

bool ASTPrinter::VisitTypedefNameDecl(TypedefNameDecl *D) {
  // TODO: VisitRedeclarable()
  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *D) {
  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitTagDecl(TagDecl *D) {
  // TODO: VisitRedeclarable()
  // TODO: getIdentifierNamespace()
  // TODO: isCompleteDefinition()
  // TODO: isEmbeddedInDeclarator()
  // TODO: isFreeStanding()
  // TODO: getExtInfo()
  // TODO: getTypedefNameForAnonDecl()
  return true;
}

bool ASTPrinter::VisitEnumDecl(EnumDecl *D) {
  // TODO: getIntegerType()
  // TODO: getPromotionType()
  // TODO: getNumPositiveBits()
  // TODO: getNumNegativeBits()
  // TODO: isScoped()
  // TODO: isScopedUsingClassTag()
  // TODO: isFixed()
  // TODO: getMemberSpecializationInfo()

  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitRecordDecl(RecordDecl *D) {
  switch (D->getTagKind()) {
  default:
    llvm_unreachable("unknown TagKind");
  case TTK_Struct:
    OS << " struct";
    break;
  case TTK_Union:
    OS << " union";
    break;
  case TTK_Class:
    OS << " class";
    break;
  }

  // TODO: hasFlexibleArrayMember()
  // TODO: isAnonymousStructOrUnion()
  // TODO: hasObjectMember()

  // FIXME: move into RAV?
  if (D->getDeclName())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitCXXRecordDecl(CXXRecordDecl *D) {
  // TODO: CXXBaseSpecifier.isVirtual()
  // TODO: CXXBaseSpecifier.isBaseOfCLass()
  // TODO: CXXBaseSpecifier.getAccessSpecifierAsWritten()
  // TODO: CXXBaseSpecifier.getInheritConstructors()
  // TODO: CXXBaseSpecifier.isPackExpansion()

  // TODO: isThisDeclarationADefinition()
  // TODO: DefinitionData

  // TODO: isLambda()
  // TODO: LambdaDefinitionData
  // TODO: getLambdaContextDecl()
  // TODO: captures_begin()/captures_end()
  return true;
}

bool ASTPrinter::TraverseClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D) {
  VisitorBase::TraverseClassTemplateSpecializationDecl(D);

  // FIXME: move into RAV
  // VisitorBase::TraverseCXXRecordHelper(D);
  if (D->isCompleteDefinition()) {
    for (CXXRecordDecl::base_class_iterator I = D->bases_begin(),
        E = D->bases_end();
        I != E; ++I) {
      TraverseTypeLoc(I->getTypeSourceInfo()->getTypeLoc());
    }
  }
  
  return true;
}

bool ASTPrinter::VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D) {
  // TODO: getSpecializedTemplateOrPartial()
  // TODO: getTemplateInstantiationArgs()
  // TODO: getSpecializationKind()
  return true;
}

bool ASTPrinter::VisitClassTemplatePartialSpecializationDecl(ClassTemplatePartialSpecializationDecl *D) {
  // FIXME: RAV should do this instead of getTemplateParameters()
  // TraverseTypeLoc(D->getTypeAsWritten()->getTypeLoc());
  return true;
}

bool ASTPrinter::VisitTemplateTypeParmDecl(TemplateTypeParmDecl *D) {
  // TODO: wasDeclaredWithTypename()
  // TODO: defaultArgumentWasInherited()

  // FIXME: move into RAV?
  if (D->getDeclName())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitEnumConstantDecl(EnumConstantDecl *D) {
  // TODO: getInitVal()

  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::TraverseIndirectFieldDecl(IndirectFieldDecl *D) {
  VisitorBase::TraverseIndirectFieldDecl(D);

  for (IndirectFieldDecl::chain_iterator
       I = D->chain_begin(),
       E = D->chain_end(); I != E; ++I)
    printDeclRef(*I, SourceLocation());

  return true;
}

bool ASTPrinter::VisitFunctionDecl(FunctionDecl *D) {
  // TODO: VisitRedeclarable()
  // TODO: getStorageClass()
  StorageClass SC = D->getStorageClassAsWritten();
  if (SC != SC_None)
    OS << ' ' << VarDecl::getStorageClassSpecifierString(SC);
  // TODO: IsInline
  if (D->isInlineSpecified())
    OS << " inline";
  if (D->isVirtualAsWritten())
    OS << " virtual";
  // TODO: isPure()
  // TODO: hasInheritedPrototype()
  // TODO: hasWrittenPrototype()
  // TODO: isDeletedAsWritten()
  // TODO: isTrivial()
  // TODO: isDefaulted()
  // TODO: isExplicitlyDefaulted()
  // TODO: hasImplicitReturnZero()
  // TODO: isConstexpr()
  // TODO: getTemplateKind()

  switch (D->getTemplatedKind()) {
  case FunctionDecl::TK_NonTemplate:
    break;
  case FunctionDecl::TK_FunctionTemplate:
    // TODO: getDescribedFunctionTemplate()
    break;
  case FunctionDecl::TK_MemberSpecialization:
    // TODO: getMemberSpecializationInfo()
    break;
  case FunctionDecl::TK_FunctionTemplateSpecialization:
    // TODO: getTemplateSpecializationInfo()
    break;
  case FunctionDecl::TK_DependentFunctionTemplateSpecialization:
    // TODO: getDependentSpecializationInfo()
    break;
  }

  return true;
}

bool ASTPrinter::VisitCXXMethodDecl(CXXMethodDecl *D) {
  // TODO: overridden_methods
  return true;
}

bool ASTPrinter::VisitCXXConstructorDecl(CXXConstructorDecl *D) {
  // TODO: IsExplicitSpecified
  // TODO: ImplicitlyDefined
  return true;
}

bool ASTPrinter::VisitCXXDestructorDecl(CXXDestructorDecl *D) {
  // TODO: ImplicitlyDefined
  // TODO: OperatorDelete
  return true;
}

bool ASTPrinter::VisitCXXConversionDecl(CXXConversionDecl *D) {
  // TODO: IsExplicitSpecified
  return true;
}

bool ASTPrinter::VisitFieldDecl(FieldDecl *D) {
  // TODO: isMutable()
  // TODO: isBitField()
  // TODO: getBitWidthValue()

  // FIXME: move into RAV?
  if (D->getDeclName())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitVarDecl(VarDecl *D) {
  // TODO: VisitRedeclarable()
  // TODO: getStorageClass()
  StorageClass SC = D->getStorageClassAsWritten();
  if (SC != SC_None)
    OS << ' ' << VarDecl::getStorageClassSpecifierString(SC);
  if (D->isThreadSpecified())
    OS << " __thread";
  // TODO: getInitStyle()
  // TODO: isExceptionVariable()
  // TODO: isNRVOVariable()
  // TODO: isCXXForRangeDecl()
  // TODO: isARCPseufoStrong()
  // TODO: isInitKnownICE()
  // TODO: isInitICE()

  // FIXME: move into RAV?
  TraverseDeclarationNameInfo(
      DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitParmVarDecl(ParmVarDecl *D) {
  // TODO: isObjCMethodParameter()
  // TODO: getFunctionScopeDepth()
  // TODO: getFunctionScopeIndex()
  // TODO: getObjCDeclQualifier()
  // TODO: isKNRPromoted()
  // TODO: hasInheritedDefaultArg()
  // TODO: hasUninstantiatedDefaultArg()
  return true;
}

bool ASTPrinter::VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *D) {
  // FIXME: move into RAV?
  if (D->getDeclName())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitRedeclarableTemplateDecl(RedeclarableTemplateDecl *D) {
  // TODO: VisitRedeclarable()
  // TODO: getInstantiatedFromMemberTemplate()
  // TODO: isMemberSpecialization()
  // TODO: getIdentifierNamespace()
  return true;
}

bool ASTPrinter::VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *D) {
  // TODO: getDepth()
  // TODO: getPosition()
  // TODO: defaultArgumentWasInherited()
  // TODO: isParameterPack()

  // FIXME: move into RAV?
  if (D->getDeclName())
    TraverseDeclarationNameInfo(
        DeclarationNameInfo(D->getDeclName(), D->getLocation()));
  return true;
}

bool ASTPrinter::VisitUsingDecl(UsingDecl *D) {
  // TODO: FirstUsingShadow.getPointer()
  // TODO: isTypeName()
  return true;
}

bool ASTPrinter::VisitUsingShadowDecl(UsingShadowDecl *D) {
  // TODO: getTargetDecl()
  // TODO: UsingOrNextShadow
  // TODO: Context.getInstantiatedFromUsingShadowDecl(D)

  printDeclRef(D->getTargetDecl(), D->getLocation());
  // Don't traverse getDeclName(), it is just getTargetDecl()->getDeclName()
  return true;
}

bool ASTPrinter::VisitLinkageSpecDecl(LinkageSpecDecl *D) {
  switch (D->getLanguage()) {
  case LinkageSpecDecl::lang_c: OS << " C"; break;
  case LinkageSpecDecl::lang_cxx: OS << " C++"; break;
  }
  return true;
}

bool ASTPrinter::VisitAccessSpecDecl(AccessSpecDecl *D) {
  switch (D->getAccess()) {
  case AS_public: OS << " public"; break;
  case AS_protected: OS << " protected"; break;
  case AS_private: OS << " private"; break;
  case AS_none: llvm_unreachable("invalid AccessSpecifier");
  }
  return true;
}

bool ASTPrinter::VisitFriendDecl(FriendDecl *D) {
  // TODO: getNextFriend()
  // TODO: isUnsupportedFriend()
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

bool ASTPrinter::VisitNullStmt(NullStmt *S) {
  // TODO: HasLeadingEmptyMacro
  return true;
}

bool ASTPrinter::VisitLabelStmt(LabelStmt *S) {
  printDeclRef(S->getDecl(), S->getIdentLoc());
  return true;
}

bool ASTPrinter::VisitAttributedStmt(AttributedStmt *S) {
  // TODO: getAttrs()
  return true;
}

bool ASTPrinter::VisitSwitchStmt(SwitchStmt *S) {
  // TODO: isAllEnumCasesCovered()
  return true;
}

bool ASTPrinter::VisitGotoStmt(GotoStmt *S) {
  printDeclRef(S->getLabel(), S->getLabelLoc());
  return true;
}

bool ASTPrinter::VisitReturnStmt(ReturnStmt *S) {
  // TODO: getNRVOCandidate()
  return true;
}

bool ASTPrinter::VisitGCCAsmStmt(GCCAsmStmt *S) {
  // TODO: isVolatile()
  // TODO: isSimple()
  // TODO: getOutputIdentifier()
  // TODO: getInputIdentifier()
  return true;
}

bool ASTPrinter::VisitExpr(Expr *E) {
  // TODO: getType()
  // TODO: isTypeDependent()
  // TODO: isValueDependent()
  // TODO: isInstantiationDependent()
  // TODO: containsUnexpandedParameterPack()
  // TODO: getValueKind()
  // TODO: getObjectKind()
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

bool ASTPrinter::VisitDeclRefExpr(DeclRefExpr *E) {
  // TODO: getFoundDecl()
  // TODO: hadMultipleCandidates()
  // TODO: refersToEnclosingLocal()
  return true;
}

bool ASTPrinter::VisitIntegerLiteral(IntegerLiteral *E) {
  bool isSigned = E->getType()->isSignedIntegerType();
  OS << ' ' << E->getValue().toString(10, isSigned);
  return true;
}

bool ASTPrinter::VisitFloatingLiteral(FloatingLiteral *E) {
  OS << ' ' << E->getValueAsApproximateDouble();
  // TODO: isExact()
  return true;
}

bool ASTPrinter::VisitStringLiteral(StringLiteral *E) {
  OS << ' ';
  E->outputString(OS);
  // TODO: getNumConcatenated()
  // TODO: getKind()
  // TODO: isPascal()
  return true;
}

bool ASTPrinter::VisitCharacterLiteral(CharacterLiteral *E) {
  OS << ' ' << E->getValue();
  // TODO: getKind()
  return true;
}

bool ASTPrinter::VisitUnaryOperator(UnaryOperator *E) {
  if (E->isPostfix())
    OS << ' ' << "postfix";
  if (E->isPrefix())
    OS << ' ' << "prefix";
  OS << ' ' << UnaryOperator::getOpcodeStr(E->getOpcode());
  return true;
}

bool ASTPrinter::VisitOffsetOfExpr(OffsetOfExpr *E) {
  // TODO: getComponent(getNumComponents())
  // TODO: getIndexExpr(getNUmExpressions)
  return true;
}

bool ASTPrinter::VisitMemberExpr(MemberExpr *E) {
  // TODO: hadMultipleCandidates()
  // TODO: getFoundDecl()
  // TODO: getType()
  // TODO: getValueKind()
  // TODO: getObjectKind()
  // TODO: isArrow()
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
  // TODO: traverse into the RecordDecl instead
  RecordDecl *D = T->getDecl();
  printIdentifier(D);
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
  // FIXME: no need to print this once everything is handled?
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
  // FIXME: handle anonymous decls
  ++Indent;
  printIndent();
  OS << "DeclarationName";
#if 0
  // TODO: display in verbose mode
  switch (NameInfo.getName().getNameKind()) {
  case DeclarationName::CXXConstructorName:
    OS << " CXXConstructorName"; break;
  case DeclarationName::CXXDestructorName:
    OS << " CXXDestructorName"; break;
  case DeclarationName::CXXConversionFunctionName:
    OS << " CXXConversionFunctionName"; break;
  case DeclarationName::Identifier:
    OS << " Identifier"; break;
  case DeclarationName::ObjCZeroArgSelector:
    OS << " ObjCZeroArgSelector"; break;
  case DeclarationName::ObjCOneArgSelector:
    OS << " ObjCOneArgSelector"; break;
  case DeclarationName::ObjCMultiArgSelector:
    OS << " ObjCMultiArgSelector"; break;
  case DeclarationName::CXXOperatorName:
    OS << " CXXOperatorName"; break;
  case DeclarationName::CXXLiteralOperatorName:
    OS << " CXXLiteralOperatorName"; break;
  case DeclarationName::CXXUsingDirective:
    OS << " CXXUsingDirective"; break;
  }
#endif
  printSourceRange(NameInfo.getSourceRange());
  OS << ' ';
  NameInfo.getName().printName(OS);
  bool Result = VisitorBase::TraverseDeclarationNameInfo(NameInfo);
  --Indent;
  return Result;
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

bool ASTPrinter::TraverseConstructorInitializer(CXXCtorInitializer *Init) {
  // FIXME: move into RAV?
  if (!Init->isWritten() && !shouldVisitImplicitCode())
    return true;

  ++Indent;
  printIndent();
  OS << "CXXCtorInitializer";
  printSourceRange(Init->getSourceRange());
  if (Init->isBaseInitializer())
    TraverseTypeLoc(Init->getTypeSourceInfo()->getTypeLoc());
  else if (Init->isAnyMemberInitializer())
    printDeclRef(Init->getAnyMember(), Init->getMemberLocation());
  TraverseStmt(Init->getInit());
  --Indent;
  return true;
}

void ASTPrinter::printNewline() {
  if (NeedLoc.isValid()) {
    OS << " <";
    printLocation(NeedLoc.getBegin(), true);
    if (NeedLoc.getBegin() != NeedLoc.getEnd()) {
      OS << "-";
      printLocation(NeedLoc.getEnd(), false);
    }
    OS << ">";
    NeedLoc = SourceRange();
  }
  if (NeedNewline) {
    OS << '\n';
    NeedNewline = false;
  }
}

void ASTPrinter::printIndent() {
  printNewline();
  for (unsigned i = 1; i < Indent; ++i)
    OS << "  ";
  NeedNewline = true;
}

// FIXME: move DeclRef traversal to RAV?
void ASTPrinter::printDeclRef(NamedDecl *D, SourceLocation Loc) {
  ++Indent;
  printIndent();
  OS << D->getDeclKindName() << "DeclRef";
  printIdentifier(D);
  printLocation(Loc);
  --Indent;
}

void ASTPrinter::printIdentifier(NamedDecl *D) {
  if (D->getIdentifier())
    OS << ' ' << D->getNameAsString();
  else
    OS << " <anon>";
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
  NeedLoc = Loc;
}

void ASTPrinter::printSourceRange(SourceRange R) {
  if (!Options.EnableLoc)
    return;
  NeedLoc = R;
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

cl::opt<bool> EnableImplicit(
    "i",
    cl::desc("Enable implicit code"),
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
  Options.EnableImplicit = EnableImplicit;
  Options.FilterString = FilterString;
  runTool(Argv, new ASTPrinterAction(Options));
  return 0;
#endif
}
