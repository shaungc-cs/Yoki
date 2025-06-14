#include "YokiASTVisitor.h"
#include "CheckerManager.h"

#define __YOKI_VISIT_NODE__(NODE)                                              \
  bool YokiASTVisitor::Visit##NODE(NODE *node) {                               \
    CheckerManager::getInstance().Visit##NODE(node, context);                  \
    return true;                                                               \
  }

#include "visit_node.inc"
#undef __YOKI_VISIT_NODE__
