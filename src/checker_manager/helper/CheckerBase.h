#ifndef C2F9D896_D044_4D91_8D6A_DD4BD6DE3ED6
#define C2F9D896_D044_4D91_8D6A_DD4BD6DE3ED6

#include <clang/AST/AST.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

using namespace clang;

class CheckerBase {
public:
#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  virtual bool Visit##NODE(NODE *node, ASTContext *context);
#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__

  // public:
  // std::string name;
  // std::string description;
  // CheckerCategory category;
};
#endif /* C2F9D896_D044_4D91_8D6A_DD4BD6DE3ED6 */
