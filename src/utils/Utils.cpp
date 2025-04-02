#include "Utils.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <regex>
#include <spdlog/spdlog.h>

std::vector<std::string>
getFilesToBeChecked(const std::string &compileCommandDir,
                    const std::vector<std::string> &excludePaths) {
  auto compileCommandFilePath = compileCommandDir + "/compile_commands.json";

  // 将字符串模式转换为正则表达式对象
  std::vector<std::regex> excludePatterns;
  for (const auto &pattern : excludePaths) {
    excludePatterns.push_back(std::regex(pattern));
  }

  std::vector<std::string> fileVecToBeChecked;
  std::ifstream file(compileCommandFilePath);
  if (!file.is_open()) {
    spdlog::error("Failed to open compile_commands.json: {}",
                  compileCommandFilePath);
    return fileVecToBeChecked;
  }
  nlohmann::json jsonData;
  file >> jsonData;
  for (const auto &entry : jsonData) {
    std::string filePath = entry["file"];
    bool exclude = false;
    for (const auto &excludePtn : excludePatterns) {
      if (std::regex_search(filePath, excludePtn)) {
        exclude = true;
        break;
      }
    }
    // 如果不在排除列表中，则添加到待检查文件列表中
    if (!exclude) {
      fileVecToBeChecked.push_back(filePath);
    }
  }
  // 关闭文件
  file.close();
  return fileVecToBeChecked;
}
