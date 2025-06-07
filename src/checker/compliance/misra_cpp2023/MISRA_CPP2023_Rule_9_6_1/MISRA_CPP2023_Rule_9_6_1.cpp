#include "MISRA_CPP2023_Rule_9_6_1.h"
#include "Defect.h"
#include "DefectManager.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include <spdlog/spdlog.h>
#include <string>

bool MISRA_CPP2023_Rule_9_6_1::VisitGotoStmt(GotoStmt *node,
                                             ASTContext *context) {

  auto defectMessage = "A goto statement shall not be used.";
  auto id = generateHashID(defectMessage);

  // 获得当前文件路径
  const auto &filePath =
      context->getSourceManager().getFilename(node->getBeginLoc()).str();
  spdlog::info("File path: {}", filePath);
  // 获得当前行号
  auto lineNumber =
      context->getSourceManager().getSpellingLineNumber(node->getBeginLoc());
  spdlog::info("Line number: {}", lineNumber);
  // 构造缺陷信息
  Defect defect(id, *this, defectMessage, filePath, lineNumber);
  DefectManager::getInstance().addDefect(defect);

  spdlog::info("MISRA_CPP2023_Rule_9_6_1: {}", defectMessage);
  return true;
}
