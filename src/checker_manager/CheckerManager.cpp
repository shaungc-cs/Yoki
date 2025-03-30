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


void CheckerManager::init(std::vector<std::string> rulesVec) {
  #define __REGISTER_CHECKER__(CHECKER) \
    registerChecker(new CHECKER()); \
  #include "misra_cpp_2023.h"
  #undef __REGISTER_CHECKER__

  if(!rulesVec.empty()) {
    std::vector<CheckerBase*> newCheckers;
    for(auto rule : checkers) {
      auto notMatch = std::find(rulesVec.begin(), rulesVec.end(), rule->name) != rulesVec.end();
      if(notMatch) {
        newCheckers.push_back(rule);
      }
    }

    checkers = newCheckers;
  }
}

CheckerManager* checkerManager = CheckerManager::getInstance();
