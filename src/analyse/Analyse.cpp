#include "Analyse.h"

#include "SastDogASTFrontendAction.h"
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

using namespace clang::tooling;

// void Analyse::analyse(std::string &path, const std::string &file) {
//   // std::string errorMsg;
//   // auto compilationDB =
//   // clang::tooling::CompilationDatabase::loadFromDirectory(
//   //     llvm::StringRef(path), errorMsg);

//   // if (!compilationDB) {
//   //   spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
//   //   return;
//   // }

//   // ClangTool Tool(*compilationDB, file);
//   // Tool.run(newFrontendActionFactory<SastDogASTFrontendAction>().get());
// }

void Analyse::analyse(
    std::shared_ptr<clang::tooling::CompilationDatabase> compilationDB,
    const std::string &file) {
  ClangTool Tool(*compilationDB, file);
  Tool.run(newFrontendActionFactory<SastDogASTFrontendAction>().get());
}
