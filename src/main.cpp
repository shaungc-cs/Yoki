#include <algorithm>
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <cstdlib>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "Analysis.h"
#include "CheckerManager.h"
#include "DefectManager.h"
#include "SastConfig.h"
#include "Utils.h"

#include "compliance_public_header.h"

using namespace clang;
using namespace clang::tooling;

// Tip: 不定义该变量会导致链接错误
int llvm::DisableABIBreakingChecks = 1;

// 自定义命令行集合，用于将命令行选项分组
static llvm::cl::OptionCategory MyToolCategory("SastDog options");

int main(int argc, const char **argv) {
  // 设置日志级别为 info
  spdlog::set_level(spdlog::level::info);

  // 清除默认options
  llvm::cl::HideUnrelatedOptions(MyToolCategory);

  // 定义一个命令行选项，并将其归类到自定义类别中
  static llvm::cl::opt<std::string> configFilePath(
      llvm::cl::Positional, llvm::cl::desc("Path to configuration file"),
      llvm::cl::Required, llvm::cl::cat(MyToolCategory));

  // 处理命令行参数
  llvm::cl::ParseCommandLineOptions(argc, argv, "SastDog\n");

  spdlog::info("Path to configuration file: " + configFilePath);

  // 读取配置文件
  // 优先考虑使用unique_ptr
  auto config = SastConfig::loadConfigFromFile(configFilePath);

  // 根据配置文件中的项目路径找到compile_command.json文件
  std::string compileCommandDir = config->getProgramPath() + "/build";
  spdlog::info("Compile command directory: " + compileCommandDir);

  // 根据compile_commands.json文件获取需要检查的文件列表
  // 会根据用户配置文件中的排除路径进行过滤
  auto fileVec = getFileVec(compileCommandDir, config->getExcludePaths());

  if (fileVec.empty()) {
    spdlog::error("No files to be checked.");
    return 1;
  }

  // 输出需要检查的文件列表
  spdlog::info("Files to be checked: " + std::to_string(fileVec.size()));
  for (const auto &file : fileVec) {
    spdlog::info("  -- " + file);
  }

  auto &checkerManager = CheckerManager::getInstance();

  // 初始化检查器，将所有系统支持的检查器全部注册到checkerManager中
  checkerManager.initializeCheckers();

  // 根据用户的配置文件重置checkerManager中的检查器
  // 若用户未显式配置，则默认启用所有检查器
  checkerManager.setUpEnabledCheckers(config->getRulesVec());
  spdlog::info("Enabled checkers: " +
               std::to_string(checkerManager.getEnabledCheckers().size()));
  // 输出启用的检查器列表
  for (auto checker : checkerManager.getEnabledCheckers()) {
    spdlog::info("---- {}", checker->getName());
  }

  // 加载compile_commands.json文件生成CompilationDatabase
  std::string errorMsg = "";
  auto compilationDB = clang::tooling::CompilationDatabase::loadFromDirectory(
      compileCommandDir, errorMsg);

  if (!compilationDB) {
    spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
    std::exit(-1);
  }
  spdlog::info("Loaded compile_commands.json successfully.");

  // complilationDB是一个unique_ptr类型智能指针，使用std::move将其转移到shared_ptr中
  std::shared_ptr compilationDBPtr = std::move(compilationDB);
  // 开始执行多线程静态分析
  Analyse::analyse(compilationDBPtr, fileVec);
  spdlog::info("Analysis finished.");

  // 输出分析结果
  spdlog::info("Size of defects: {}", DefectManager::getInstance().size());
  auto &defectManager = DefectManager::getInstance();
  defectManager.setSastConfig(std::move(config));
  defectManager.dumpAsJson();
  defectManager.dumpAsHtml();

  // 释放资源
  CheckerManager::getInstance().clearCheckers();
  defectManager.clearDefects();
  compilationDBPtr.reset();
  fileVec.clear();
  spdlog::info("SastDog finished running.");
  return 0;
}
