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

  checkerManager->init(config->getRulesVec());

  // 根据项目路径找到compile_command.json文件
  std::string compileCommandDir = config->getProgramPath() + "/build";

  std::string errorMsg = "";
  auto compilationDB = clang::tooling::CompilationDatabase::loadFromDirectory(
      compileCommandDir, errorMsg);

  if (!compilationDB) {
    spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
    return 1;
  }

  std::shared_ptr compilationDBPtr = std::move(compilationDB);

  auto fileVecToBeChecked =
      getFilesToBeChecked(compileCommandDir, config->getExcludePaths());

  Analyse::analyse(compilationDBPtr, fileVecToBeChecked);
}
