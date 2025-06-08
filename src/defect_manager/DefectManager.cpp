#include "DefectManager.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>

void DefectManager::addDefect(const Defect &defect) {
  // 锁定互斥量，确保线程安全
  std::lock_guard<std::mutex> lock(defectMutex);
  // 插入缺陷到管理器中
  defects.push_back(defect);
}

void DefectManager::dumpAsJson() {}

void DefectManager::dumpAsHtml() {
  // 将缺陷信息以HTML格式输出
  // 在当前路径下创建一个名为report.html的文件，如果存在则覆盖
  std::ofstream htmlFile("report.html");
  if (!htmlFile.is_open()) {
    std::cerr << "Failed to open report.html for writing." << std::endl;
    return;
  }
  for (const auto &defect : defects) {
    htmlFile << "<div class=\"defect\">" << std::endl;
    htmlFile << "  <h2>Defect ID: " << defect.getDefectId() << "</h2>"
             << std::endl;
    htmlFile << "  <p>File: " << defect.getFilePath() << "</p>" << std::endl;
    htmlFile << "  <p>Line: " << defect.getLineNumber() << "</p>" << std::endl;
    htmlFile << "  <p>Message: " << defect.getDefectMessage() << "</p>"
             << std::endl;
    htmlFile << "</div>" << std::endl;
  }
  htmlFile.close();
  spdlog::info("Defects dumped to report.html successfully.");
}
