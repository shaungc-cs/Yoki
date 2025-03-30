#include "CheckerManager.h"
#define __REGISTER_CHECKER__(CHECKER) class CHECKER;
#include "misra_cpp_2023.inc"
#undef __REGISTER_CHECKER__

bool CheckerManager::registerChecker(CheckerBase *checker) {
  if (checker) {
    enabledCheckerVec.push_back(checker);
    return true;
  }
  return false;
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

void CheckerManager::init(std::vector<std::string> rulesVec) {
#define __REGISTER_CHECKER__(CHECKER) registerChecker(new CHECKER());
#include "misra_cpp_2023.inc"
#undef __REGISTER_CHECKER__

  if (!rulesVec.empty()) {
    // std::vector<CheckerBase *> newCheckers;
    // for (auto rule : enabledCheckerVec) {
    //   auto notMatch = std::find(rulesVec.begin(), rulesVec.end(), rule->name)
    //   !=
    //                   rulesVec.end();
    //   if (notMatch) {
    //     newCheckers.push_back(rule);
    //   }
    // }

    // enabledCheckerVec = newCheckers;
  }
}

CheckerManager *checkerManager = CheckerManager::getInstance();
