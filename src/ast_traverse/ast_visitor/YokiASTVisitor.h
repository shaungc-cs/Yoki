#ifndef D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7
#define D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

class YokiASTVisitor : public RecursiveASTVisitor<YokiASTVisitor> {
public:
  explicit YokiASTVisitor(ASTContext *context) : context(context) {}

#define __YOKI_VISIT_NODE__(NODE) bool Visit##NODE(NODE *node);
#include "visit_node.inc"
#undef __YOKI_VISIT_NODE__

private:
  ASTContext *context;
};

#endif /* D55EFA00_8DA0_4BFB_8F83_6B87A49E69D7 */
