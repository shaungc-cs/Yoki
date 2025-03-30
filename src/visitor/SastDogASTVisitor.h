#ifndef D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7
#define D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;


class SastDogASTVisitor : public RecursiveASTVisitor<SastDogASTVisitor> {
  public:
    explicit SastDogASTVisitor(ASTContext *Context) : Context(Context) {}

    #define __SAST_DOG_VISIT_NODE__(NODE) bool Visit##NODE(NODE *node);
    #include "checkers.inc"
    #undef __SAST_DOG_VISIT_NODE__


    private:
    ASTContext *Context;
    // RulesManager rulesManager = RulesManager::getInstance();
};


#endif /* D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7 */
