#pragma once

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
