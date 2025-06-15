#include "YokiConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

// 静态成员变量定义
YokiConfig& YokiConfig::getInstance() {
  static YokiConfig instance;
  return instance;
}

std::string YokiConfig::getProgramName() { return programName; }

std::string YokiConfig::getProgramPath() { return programPath; }

std::vector<std::string> YokiConfig::getRulesVec() { return rulesVec; }

std::vector<std::string> YokiConfig::getExcludePaths() { return excludePaths; }

std::string YokiConfig::getMode() { return mode; }

bool YokiConfig::isStaticAnalysis() { 
  return mode == "static_analysis"; 
}

bool YokiConfig::isTUGeneration() { 
  return mode == "tu_generation" ; 
}

bool YokiConfig::loadConfigFromFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    spdlog::error("Failed to open config file: {}", filePath);
    return false;
  }

  json config;
  file >> config;

  // 文件格式
  // {
  //   "program_name" : "Program Name",
  //   "program_path" : "path/to/program",
  //   "rules_enabled": [ "rule1", "rule2", "rule3" ],
  //   "exclude_paths" : [ "path1", "path2", "path3" ],
  //   "mode" : "scan|report|analyze"
  // }

  // 读取 JSON 数据
  programName = config["program_name"];
  programPath = config["program_path"];
  rulesVec = config["rules_enabled"].get<std::vector<std::string>>();
  excludePaths = config["exclude_paths"].get<std::vector<std::string>>();
  
  // 读取mode字段，如果不存在则设置默认值
  if (config.contains("mode")) {
    mode = config["mode"];
  } else {
    mode = "scan"; // 默认模式
  }

  spdlog::info("Successfully load config from {}", filePath);
  spdlog::info("Program name: " + programName);
  spdlog::info("Program path: " + programPath);
  spdlog::info("Mode: " + mode);
  spdlog::info("Rules enabled: ");
  for (const auto &rule : rulesVec) {
    spdlog::info("  ---- " + rule);
  }
  spdlog::info("Exclude paths: ");
  for (const auto &path : excludePaths) {
    spdlog::info("  ---- " + path);
  }
  
  // 关闭文件
  file.close();
  return true;
}
