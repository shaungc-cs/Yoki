#include "CheckerManager.h"
#include "CheckerUtils.h"
#include <spdlog/spdlog.h>

// #define STRINGIFY(x) #x
// #define TOSTRING(x) STRINGIFY(x)

// #define __REGISTER_CHECKER__(STANDARD_NAME, CLASS_NAME, CHECKER_NAME, DESC,    \
//                              SEVERITY)                                         \
//   TOSTRING(include STANDARD_NAME / CLASS_NAME.h)
// #include "misra_cpp2023/misra_cpp2023.inc";
// #undef __REGISTER_CHECKER__
// #undef TOSTRING
// #undef STRINGIFY

void CheckerManager::initializeCheckers() {

  // #define __REGISTER_CHECKER__(STANDARD_NAME, CLASS_NAME, CHECKER_NAME, DESC,    \
//                              SEVERITY)                                         \
//   enabledCheckerVec.push_back(                                                 \
//       new CLASS_NAME(CHECKER_NAME, DESC, CheckerSeverity::SEVERITY));
  // #include "misra_cpp2023/misra_cpp2023.inc";
}

bool CheckerManager::registerChecker(CheckerBase *checker) {
  if (checker) {
    spdlog::info("Register checker: {}", checker->getName());
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
