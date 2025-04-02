#include "CheckerManager.h"
#include "CheckerUtils.h"
#include <spdlog/spdlog.h>

#include "compliance_public_header.h"

void CheckerManager::initializeCheckers() {
#define __REGISTER_CHECKER__(STANDARD_NAME, CLASS_NAME, CHECKER_NAME, DESC,    \
                             SEVERITY)                                         \
  enabledCheckerVec.push_back(                                                 \
      new CLASS_NAME(CHECKER_NAME, DESC, CheckerSeverity::SEVERITY));
#include "misra_cpp2023/misra_cpp2023.inc";
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

    for (auto name : rulesVec) {
      auto it = std::find_if(
          enabledCheckerVec.begin(), enabledCheckerVec.end(),
          [&name](CheckerBase *checker) { return checker->getName() == name; });
      if (it != enabledCheckerVec.end()) {
        newCheckers.push_back(*it);
      } else {
        spdlog::warn("Checker {} not found", name);
      }
    }

    enabledCheckerVec = newCheckers;
  }
}
