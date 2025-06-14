#include "YokiASTFrontendAction.h"
#include "YokiASTConsumer.h"
#include <clang/Frontend/CompilerInstance.h>
#include <memory>

std::unique_ptr<clang::ASTConsumer> YokiASTFrontendAction::CreateASTConsumer(
    clang::CompilerInstance &CI, [[maybe_unused]] llvm::StringRef InFile) {
  return std::make_unique<YokiASTConsumer>(&CI.getASTContext());
}
