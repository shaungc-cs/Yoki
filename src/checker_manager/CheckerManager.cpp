#include "CheckerManager.h"
#include "CheckerUtils.h"

bool CheckerManager::registerChecker(CheckerBase *checker) {
  if (checker) {
    enabledCheckerVec.push_back(checker);
    return true;
  }
  return false;
}

bool CheckerManager::clearCheckers() {
  for (auto checker : enabledCheckerVec) {
    delete checker;
  }
  enabledCheckerVec.clear();
  return true;
}

#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  bool CheckerManager::Visit##NODE(NODE *node, ASTContext *context) {          \
    for (auto checker : enabledCheckerVec) {                                   \
      if (checker->Visit##NODE(node, context)) {                               \
        return true;                                                           \
      }                                                                        \
    }                                                                          \
    return false;                                                              \
  }
#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__

void CheckerManager::setUpEnabledCheckers(std::vector<std::string> rulesVec) {
  if (!rulesVec.empty()) {
    std::vector<CheckerBase *> newCheckers;
    for (auto rule : enabledCheckerVec) {
      auto notMatch = std::find(rulesVec.begin(), rulesVec.end(),
                                rule->getName()) != rulesVec.end();
      if (notMatch) {
        newCheckers.push_back(rule);
      }
    }

    enabledCheckerVec = newCheckers;
  }
}
