#pragma once

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

class SastDogASTVisitor : public RecursiveASTVisitor<SastDogASTVisitor> {
  public:
    bool VisitCXXMethodDecl(CXXMethodDecl *Method) override;
};
