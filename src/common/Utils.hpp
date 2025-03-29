#include <fstream>
#include <nlohmann/json.hpp>
#include <regex>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

static std::vector<std::string>
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
  // 解析 JSON 文件
  nlohmann::json jsonData;
  file >> jsonData;
  // 遍历 JSON 数组
  for (const auto &entry : jsonData) {
    // 获取文件路径
    std::string filePath = entry["file"];
    // 检查文件路径是否在排除列表中
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