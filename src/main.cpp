#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "Analysis.h"
#include "CheckerManager.h"
#include "DefectManager.h"
#include "MISRA_CPP2023_Rule_9_6_1.h"
#include "SastConfig.h"
#include "Utils.h"

using namespace clang;
using namespace clang::tooling;

// 不定义该变量会导致链接错误
int llvm::DisableABIBreakingChecks = 1;

// 定义自定义命令行集合
static llvm::cl::OptionCategory MyToolCategory("SastDog options");

int main(int argc, const char **argv) {
  // 设置日志级别为 info
  spdlog::set_level(spdlog::level::info);

  llvm::cl::HideUnrelatedOptions(MyToolCategory);

  // 定义一个命令行选项，并将其归类到自定义类别中
  static llvm::cl::opt<std::string> configFilePath(
      llvm::cl::Positional, llvm::cl::desc("Path to configuration file"),
      llvm::cl::Required, llvm::cl::cat(MyToolCategory));

  llvm::cl::ParseCommandLineOptions(argc, argv, "SastDog\n");

  spdlog::info("Path to configuration file: " + configFilePath);

  // 读取配置文件
  auto config = SastConfig::loadConfigFromFile(configFilePath);
  if (!config) {
    spdlog::error("Failed to load config file");
    return 1;
  }

  // 根据项目路径找到compile_command.json文件
  std::string compileCommandDir = config->getProgramPath() + "/build";
  spdlog::info("Compile command directory: " + compileCommandDir);

  std::string errorMsg = "";
  auto compilationDB = clang::tooling::CompilationDatabase::loadFromDirectory(
      compileCommandDir, errorMsg);

  if (!compilationDB) {
    spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
    return 1;
  }
  spdlog::info("Loaded compile_commands.json successfully.");

  std::shared_ptr compilationDBPtr = std::move(compilationDB);

  auto fileVecToBeChecked =
      getFilesToBeChecked(compileCommandDir, config->getExcludePaths());
  if (fileVecToBeChecked.empty()) {
    spdlog::error("No files to be checked.");
    return 1;
  }
  spdlog::info("Files to be checked: " +
               std::to_string(fileVecToBeChecked.size()));
  for (const auto &file : fileVecToBeChecked) {
    spdlog::info("  -- " + file);
  }

  // 设置开启的检查器
  auto checkerManager = CheckerManager::getInstance();
  checkerManager->registerChecker(
      new MISRA_CPP2023_Rule_9_6_1("MISRA_CPP:Rule 9.6.1",
                                   "A goto statement "
                                   "shall not be used.",
                                   CheckerCategory::ADVISORY));
  checkerManager->setUpEnabledCheckers(config->getRulesVec());

  Analyse::analyse(compilationDBPtr, fileVecToBeChecked);

  spdlog::info("Size of defects: {}", DefectManager::getInstance()->size());

  auto defectManager = DefectManager::getInstance();
  defectManager->setSastConfig(config);
  defectManager->dumpAsJson();
  defectManager->dumpAsHtml();

  // 释放资源
  CheckerManager::getInstance()->clearCheckers();
  defectManager->clearDefects();
  compilationDBPtr.reset();
  fileVecToBeChecked.clear();
  config.reset();
  spdlog::info("SastDog finished running.");
  return 0;
}
