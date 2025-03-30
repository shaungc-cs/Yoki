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
#include "Config.h"
// #include "ThreadPool.h"
#include "Utils.h"

#include "CheckerManager.h"

using namespace clang;
using namespace clang::tooling;

int llvm::DisableABIBreakingChecks = 1;

// Command line options
static llvm::cl::OptionCategory MyToolCategory("SastDog options");

int main(int argc, const char **argv) {
  // 设置日志级别为 info
  spdlog::set_level(spdlog::level::info);

  llvm::cl::HideUnrelatedOptions(MyToolCategory);

  // 定义一个命令行选项，并将其归类到自定义类别中
  static llvm::cl::opt<std::string> configFilePath(
      llvm::cl::Positional, llvm::cl::desc("path to compile_command.json"),
      llvm::cl::Required, llvm::cl::cat(MyToolCategory));

  llvm::cl::ParseCommandLineOptions(argc, argv, "SastDog\n");

  spdlog::info("Path to configuration file: " + configFilePath);

  // 读取配置文件
  auto config = Config::loadConfigFromFile(configFilePath);
  if (!config) {
    spdlog::error("Failed to load config file");
    return 1;
  }

  checkerManager->init(config->getRulesVec());
  
  // 根据项目路径找到compile_command.json文件
  std::string compileCommandDir = config->getProgramPath() + "/build";

  std::string errorMsg;
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
