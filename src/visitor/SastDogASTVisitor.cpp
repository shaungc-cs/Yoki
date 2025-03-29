#include "SastDogASTVisitor.h"

bool SastDogASTVisitor::VisitCXXMethodDecl(CXXMethodDecl *Method) {
  if (Method->isThisDeclarationADefinition()) {
    llvm::outs() << Method->getQualifiedNameAsString() << "\n";
  }
  return true;
}
