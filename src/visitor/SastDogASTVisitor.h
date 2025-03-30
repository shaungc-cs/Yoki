#pragma once

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;


class SastDogASTVisitor : public RecursiveASTVisitor<SastDogASTVisitor> {
  public:
    explicit SastDogASTVisitor(ASTContext *Context) : Context(Context) {}

#ifndef VISITOR_VISIT_ASTNODE
#define VISITOR_VISIT_ASTNODE(Node) \
  bool Visit##Node(Node *node){ \
    rulesManager.Visit##Node(node, Context); \
    return true; \
  } \
#endif



    private:
    ASTContext *Context;
    RulesManager rulesManager = RulesManager::getInstance();
};
