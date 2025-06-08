#include "SastDogASTFrontendAction.h"
#include "SastDogASTConsumer.h"
#include <clang/Frontend/CompilerInstance.h>
#include <memory>

std::unique_ptr<clang::ASTConsumer> SastDogASTFrontendAction::CreateASTConsumer(
    clang::CompilerInstance &CI, [[maybe_unused]] llvm::StringRef InFile) {
  return std::make_unique<SastDogASTConsumer>(&CI.getASTContext());
}
