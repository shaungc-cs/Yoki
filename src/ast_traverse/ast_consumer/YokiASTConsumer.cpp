#include "YokiASTConsumer.h"

void YokiASTConsumer::HandleTranslationUnit(clang::ASTContext &context) {
  visitor.TraverseDecl(context.getTranslationUnitDecl());
}
