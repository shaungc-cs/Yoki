#include "SastDogASTFrontendAction.h"
#include "SastDogASTConsumer.h"
#include <memory>

std::unique_ptr<clang::ASTConsumer>
SastDogASTFrontendAction::CreateASTConsumer(clang::CompilerInstance &CI,
                                            llvm::StringRef InFile) {
  return std::make_unique<SastDogASTConsumer>();
}
