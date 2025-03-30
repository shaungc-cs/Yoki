#include "SastDogASTVisitor.h"
#include "CheckerManager.h"

#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  bool SastDogASTVisitor::Visit##NODE(NODE *node) {                            \
    checkerManager->Visit##NODE(node, context);                                \
    return true;                                                               \
  }

#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__
