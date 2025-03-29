#pragma once

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

class SastDogASTVisitor : public RecursiveASTVisitor<SastDogASTVisitor> {
  public:
    explicit SastDogASTVisitor(ASTContext *Context) : Context(Context) {}
    bool VisitCXXMethodDecl(CXXMethodDecl *Method);

    private:
    ASTContext *Context;
};
