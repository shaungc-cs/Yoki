#include "YokiUTGenerationASTConsumer.h"
#include "YokiConfig.h"

void YokiUTGenerationASTConsumer::HandleTranslationUnit(
    clang::ASTContext &context) {
  visitor.TraverseDecl(context.getTranslationUnitDecl());
}
