#ifndef FC5C20E8_3E50_433A_A8A4_209A596BBFEA
#define FC5C20E8_3E50_433A_A8A4_209A596BBFEA

#include "SastDogASTVisitor.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <spdlog/spdlog.h>

class SastDogASTConsumer : public clang::ASTConsumer {
public:
  explicit SastDogASTConsumer(ASTContext *context) : visitor(context) {}
  virtual void HandleTranslationUnit(clang::ASTContext &context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
  }

private:
  SastDogASTVisitor visitor;
};

#endif /* FC5C20E8_3E50_433A_A8A4_209A596BBFEA */
