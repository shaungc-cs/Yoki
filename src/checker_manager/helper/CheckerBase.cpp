#include "CheckerBase.h"

#define __SAST_DOG_VISIT_NODE__(NODE) \
bool CheckerBase::Visit##NODE(NODE *node, ASTContext* context){ \
  return true; \
}

#include "checkers.inc"
#undef __SAST_DOG_VISIT_NODE__
