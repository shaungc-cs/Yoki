#include "YokiStaticScanASTConsumer.h"
#include "YokiConfig.h"

void YokiStaticScanASTConsumer::HandleTranslationUnit(
    clang::ASTContext &context) {
  visitor.TraverseDecl(context.getTranslationUnitDecl());
}
