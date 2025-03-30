#include "CheckerManager.h"

bool CheckerManager::registerChecker(CheckerBase* checker) {
  if (checker) {
    checkers.push_back(checker);
    return true;
  }
  return false;
}

  #define __SAST_DOG_VISIT_NODE__(NODE) bool CheckerManager::Visit##NODE(NODE *node, ASTContext *context){ \
    for (auto checker : checkers) { \
      if (checker->Visit##NODE(node, context)) { \
        return true; \
      } \
    } \
    return false; \
  }
  #include "checkers.inc"
  #undef __SAST_DOG_VISIT_NODE__


CheckerManager* checkerManager = CheckerManager::getInstance();
