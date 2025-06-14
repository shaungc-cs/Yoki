#ifndef FC5C20E8_3E50_433A_A8A4_209A596BBFEA
#define FC5C20E8_3E50_433A_A8A4_209A596BBFEA

#include "YokiASTVisitor.h"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>

class YokiASTConsumer : public clang::ASTConsumer {
public:
  explicit YokiASTConsumer(ASTContext *context) : visitor(context) {}
  virtual void HandleTranslationUnit(clang::ASTContext &context);

private:
  YokiASTVisitor visitor;
};

#endif /* FC5C20E8_3E50_433A_A8A4_209A596BBFEA */
