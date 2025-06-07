#include "SastDogASTConsumer.h"

void SastDogASTConsumer::HandleTranslationUnit(clang::ASTContext &context) {
  visitor.TraverseDecl(context.getTranslationUnitDecl());
}
