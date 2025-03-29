#pragma once

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

#ifndef VISITOR_VISIT_ASTNODE
#define VISITOR_VISIT_ASTNODE(Node) \
  bool Visit##Node(Node *node){ \
    rulesManager.Visit##Node(node, Context); \
    return true; \
  } \
#endif


class SastDogASTVisitor : public RecursiveASTVisitor<SastDogASTVisitor> {
  public:
    explicit SastDogASTVisitor(ASTContext *Context) : Context(Context) {}
    VISITOR_VISIT_ASTNODE(Decl)
    VISITOR_VISIT_ASTNODE(NamedDecl)
    VISITOR_VISIT_ASTNODE(ValueDecl)
    VISITOR_VISIT_ASTNODE(FunctionDecl)
    VISITOR_VISIT_ASTNODE(VarDecl)
    VISITOR_VISIT_ASTNODE(FieldDecl)
    VISITOR_VISIT_ASTNODE(TypedefDecl)
    VISITOR_VISIT_ASTNODE(NamespaceDecl)
    VISITOR_VISIT_ASTNODE(CXXRecordDecl)
    VISITOR_VISIT_ASTNODE(CXXMethodDecl)
    VISITOR_VISIT_ASTNODE(CXXConstructorDecl)
    VISITOR_VISIT_ASTNODE(CXXDestructorDecl)


    VISITOR_VISIT_ASTNODE(Type)
    VISITOR_VISIT_ASTNODE(BuiltinType)
    VISITOR_VISIT_ASTNODE(PointerType)
    VISITOR_VISIT_ASTNODE(ArrayType)


    VISITOR_VISIT_ASTNODE(Stmt)
    VISITOR_VISIT_ASTNODE(CompoundStmt)
    VISITOR_VISIT_ASTNODE(IfStmt)
    VISITOR_VISIT_ASTNODE(ForStmt)
    VISITOR_VISIT_ASTNODE(WhileStmt)
    VISITOR_VISIT_ASTNODE(ReturnStmt)

    VISITOR_VISIT_ASTNODE(Expr)
    VISITOR_VISIT_ASTNODE(UnaryOperator)
    VISITOR_VISIT_ASTNODE(BinaryOperator)
    VISITOR_VISIT_ASTNODE(CallExpr)
    VISITOR_VISIT_ASTNODE(CXXConstructExpr)
    VISITOR_VISIT_ASTNODE(CXXMemberCallExpr)
    VISITOR_VISIT_ASTNODE(CXXNewExpr)
    VISITOR_VISIT_ASTNODE(CXXDeleteExpr)

    private:
    ASTContext *Context;
    RulesManager rulesManager = RulesManager::getInstance();
};
