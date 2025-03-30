#include "SastDogASTVisitor.h"


#define __SAST_DOG_VISIT_NODE__(NODE) \
  bool SastDogASTVisitor::Visit##NODE(NODE *node){ \
    node; \
    return true; \
  }

#include "checkers.inc"
#undef __SAST_DOG_VISIT_NODE__

