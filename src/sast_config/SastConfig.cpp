#include "SastConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

std::string SastConfig::getProgramName() { return programName; }

std::string SastConfig::getProgramPath() { return programPath; }

std::vector<std::string> SastConfig::getRulesVec() { return rulesVec; }

std::vector<std::string> SastConfig::getExcludePaths() { return excludePaths; }

std::shared_ptr<SastConfig>
SastConfig::loadConfigFromFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    spdlog::error("Failed to open config file: {}", filePath);
    return nullptr;
  }

  // 解析 JSON 文件
  json config;
  file >> config;

  // {
  //   "program_name" : "Program Name",
  //   "program_path" : "path/to/program",
  //   "rules_enabled": [ "rule1", "rule2", "rule3" ],
  //   "exclude_paths" : [ "path1", "path2", "path3" ]
  // }

  // 读取 JSON 数据
  std::string programName = config["program_name"];
  std::string programPath = config["program_path"];
  std::vector<std::string> rulesVec =
      config["rules_enabled"].get<std::vector<std::string>>();
  std::vector<std::string> excludePaths =
      config["exclude_paths"].get<std::vector<std::string>>();
  // 创建 Config 对象
  std::shared_ptr<SastConfig> configObj = std::make_shared<SastConfig>(
      programName, programPath, rulesVec, excludePaths);
  spdlog::info("Successfully load config from {}", filePath);
  spdlog::info("Program name: " + programName);
  spdlog::info("Program path: " + programPath);
  spdlog::info("Rules enabled: ");
  for (const auto &rule : rulesVec) {
    spdlog::info("  --" + rule);
  }
  spdlog::info("Exclude paths: ");
  for (const auto &path : excludePaths) {
    spdlog::info("  --" + path);
  }
  // 关闭文件
  file.close();
  return configObj;
}
