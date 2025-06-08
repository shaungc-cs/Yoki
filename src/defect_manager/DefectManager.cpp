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
  // 写入HTML头部信息
  htmlFile << "<!DOCTYPE html>" << std::endl;
  htmlFile << "<html lang=\"en\">" << std::endl;
  htmlFile << "<head>" << std::endl;
  htmlFile << "  <meta charset=\"UTF-8\">" << std::endl;
  htmlFile << "  <meta name=\"viewport\" content=\"width=device-width, "
              "initial-scale=1.0\">"
           << std::endl;
  htmlFile << "  <title>SastDog Defect Report</title>" << std::endl;
  htmlFile << "  <style>" << std::endl;
  htmlFile << "    body { font-family: Arial, sans-serif; margin: 20px; }"
           << std::endl;
  htmlFile << "    .defect { border: 1px solid #ccc; padding: 10px; "
              "margin-bottom: 10px; }"
           << std::endl;
  htmlFile << "    .defect h2 { margin: 0; }" << std::endl;
  htmlFile << "    .defect p { margin: 5px 0; }" << std::endl;
  htmlFile << "  </style>" << std::endl;
  htmlFile << "</head>" << std::endl;
  // 将logo照片添加到HTML文件中
  htmlFile << "<body>" << std::endl;
  htmlFile << "  <h1>SastDog Defect Report</h1>" << std::endl;
  // 遍历所有缺陷并写入HTML文件
  for (const auto &defect : defects) {
    htmlFile << "<div class=\"defect\">" << std::endl;
    htmlFile << "  <p>File: " << defect.getFilePath() << "</p>" << std::endl;
    htmlFile << "  <p>Line: " << defect.getLineNumber() << "</p>" << std::endl;
    htmlFile << "  <p>Message: " << defect.getDefectMessage() << "</p>"
             << std::endl;
    htmlFile << "</div>" << std::endl;
  }
  htmlFile.close();
  spdlog::info("Defects dumped to report.html successfully.");
}
