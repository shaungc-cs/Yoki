#ifndef B9A6BE48_F3D8_4505_810D_31AD3F9EE71B
#define B9A6BE48_F3D8_4505_810D_31AD3F9EE71B

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

class YokiUTGenerationASTViositor : public RecursiveASTVisitor<YokiUTGenerationASTViositor> {
public:
  explicit YokiUTGenerationASTViositor(ASTContext *context) : context(context) {}

#define __YOKI_VISIT_NODE__(NODE) bool Visit##NODE(NODE *node);
#include "visit_node.inc"
#undef __YOKI_VISIT_NODE__

private:
  ASTContext *context;
};

#endif /* B9A6BE48_F3D8_4505_810D_31AD3F9EE71B */
