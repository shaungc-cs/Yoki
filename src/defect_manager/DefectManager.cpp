#include "DefectManager.h"
#include <iostream>

void DefectManager::addDefect(const Defect &defect) {
  // 锁定互斥量，确保线程安全
  std::lock_guard<std::mutex> lock(defectMutex);
  // 插入缺陷到管理器中
  defects.push_back(defect);
}

void DefectManager::dumpAsJson() {
  // 将缺陷信息以JSON格式输出
  for (const auto &defect : defects) {
    // 输出缺陷信息
    std::cout << defect.getDefectId() << " "
              << defect.getBelongingChecker()->getName() << " "
              << defect.getDefectMessage() << " " << std::endl;
  }
}

void DefectManager::dumpAsHtml() {
  // 将缺陷信息以HTML格式输出
  for (const auto &defect : defects) {
    // 输出缺陷信息
  }
}
