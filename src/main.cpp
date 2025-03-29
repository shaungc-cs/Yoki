#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "Config.h"
#include "Utils.hpp"

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

  // 根据项目路径找到compile_command.json文件
  auto compileCommandDir = config->getProgramPath() + "/build";

  auto fileVecToBeChecked =
      getFilesToBeChecked(compileCommandDir, config->getExcludePaths());

  std::string errorMsg;
  auto compilationDB =
      CompilationDatabase::loadFromDirectory(compileCommandDir, errorMsg);

  if (!compilationDB) {
    spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
    return 1;
  }

  ClangTool Tool(*compilationDB, fileVecToBeChecked);
}
