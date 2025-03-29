#pragma once
#include <clang/Frontend/FrontendActions.h>
#include <memory>

class SastDogASTFrontendAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    llvm::StringRef InFile) override;
};
