#ifndef B1881690_E66F_4CC2_A176_D1C0D7F95697
#define B1881690_E66F_4CC2_A176_D1C0D7F95697

#include "YokiUTGenerationASTViositor.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <spdlog/spdlog.h>

class YokiUTGenerationASTConsumer : public clang::ASTConsumer {
public:
  explicit YokiUTGenerationASTConsumer(ASTContext *context) : visitor(context) {
    spdlog::info("YokiUTGenerationASTConsumer initialized.");
  }
  virtual void HandleTranslationUnit(clang::ASTContext &context);

private:
YokiUTGenerationASTViositor visitor;
};

#endif /* B1881690_E66F_4CC2_A176_D1C0D7F95697 */
