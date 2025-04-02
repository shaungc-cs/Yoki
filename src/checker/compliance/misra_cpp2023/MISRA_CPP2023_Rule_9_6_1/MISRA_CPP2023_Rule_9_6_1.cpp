#include "MISRA_CPP2023_Rule_9_6_1.h"
#include <spdlog/spdlog.h>

bool MISRA_CPP2023_Rule_9_6_1::VisitGotoStmt(GotoStmt *node,
                                             ASTContext *context) {

  auto defectMessage = "A goto statement shall not be used.";
  auto id = generateHashID(defectMessage);
  Defect defect(id, this, defectMessage, node->getSourceRange());
  DefectManager::getInstance()->addDefect(defect);

  spdlog::info("MISRA_CPP2023_Rule_9_6_1: {}", defectMessage);
  return true;
}
