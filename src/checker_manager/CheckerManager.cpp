#include "CheckerManager.h"
#include "CheckerUtils.h"
#include <spdlog/spdlog.h>

#include "compliance_public_header.h"

void CheckerManager::initializeCheckers() {
#define __REGISTER_CHECKER__(STANDARD_NAME, CLASS_NAME, CHECKER_NAME, DESC,    \
                             SEVERITY)                                         \
  enabledCheckerVec.emplace_back(CHECKER_NAME, DESC, CheckerSeverity::SEVERITY);
#include "misra_cpp2023/misra_cpp2023.inc";
}

bool CheckerManager::clearCheckers() {
  supportCheckerVec.clear();
  return true;
}

#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  bool CheckerManager::Visit##NODE(NODE *node, ASTContext *context) {          \
    for (auto checker : enabledCheckerVec) {                                   \
      if (checker.Visit##NODE(node, context)) {                                \
        return true;                                                           \
      }                                                                        \
    }                                                                          \
    return false;                                                              \
  }
#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__

void CheckerManager::setUpEnabledCheckers(
    const std::vector<std::string> &rulesVec) {
  if (!rulesVec.empty()) {

    for (const auto &name : rulesVec) {
      bool found = false;
      for (auto &checker : supportCheckerVec) {
        if (checker.getName() == name) {
          enabledCheckerVec.push_back(checker);
          found = true;
          break;
        }
      }
      if (!found) {
        spdlog::warn("Checker {} not found in support checkers", name);
      }
    }
  }
}
