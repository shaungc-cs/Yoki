#include "DefectManager.h"
#include "spdlog/spdlog.h"

void DefectManager::addDefect(const Defect &defect) {
  // 锁定互斥量，确保线程安全
  std::lock_guard<std::mutex> lock(defectMutex);
  // 插入缺陷到管理器中
  defects.push_back(defect);
}

void DefectManager::dumpAsJson() {}

void DefectManager::dumpAsHtml() {
  // 将缺陷信息以HTML格式输出
  for (const auto &defect : defects) {
    // 输出缺陷信息
    spdlog::info("Defect ID: {}", defect.getDefectId());
    spdlog::info("Checker: {}", defect.getBelongingChecker().getName());
    spdlog::info("Message: {}", defect.getDefectMessage());
    spdlog::info("File: {}", defect.getFilePath());
    spdlog::info("Line: {}", defect.getLineNumber());
    spdlog::info("--------------------------------------------------");
  }
}
