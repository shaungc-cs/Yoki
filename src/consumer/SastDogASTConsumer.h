#ifndef FC5C20E8_3E50_433A_A8A4_209A596BBFEA
#define FC5C20E8_3E50_433A_A8A4_209A596BBFEA

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include "SastDogASTVisitor.h"

class SastDogASTConsumer : public clang::ASTConsumer {
public:
  explicit SastDogASTConsumer(ASTContext* Context) : visitor(Context) {}
  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  SastDogASTVisitor visitor;
};


#endif /* FC5C20E8_3E50_433A_A8A4_209A596BBFEA */
