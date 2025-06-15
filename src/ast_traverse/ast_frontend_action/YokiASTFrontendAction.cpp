#include "YokiASTFrontendAction.h"
#include "YokiStaticScanASTConsumer.h"
#include "YokiUTGenerationASTConsumer.h"
#include <clang/Frontend/CompilerInstance.h>
#include <memory>
#include <YokiConfig.h>
#include <spdlog/spdlog.h>

std::unique_ptr<clang::ASTConsumer> YokiASTFrontendAction::CreateASTConsumer(
    clang::CompilerInstance &CI, [[maybe_unused]] llvm::StringRef InFile) {

    if(YokiConfig::getInstance().isStaticAnalysis()) {
        spdlog::info("Creating ASTConsumer for static analysis mode.");
        // 如果是静态分析模式，使用 YokiStaticScanASTConsumer
        return std::make_unique<YokiStaticScanASTConsumer>(&CI.getASTContext());
    } else if (YokiConfig::getInstance().isTUGeneration()) {
        spdlog::info("Creating ASTConsumer for unit test generation mode.");
        // 如果是单元生成模式，使用 YokiUTGenerationASTConsumer
        return std::make_unique<YokiUTGenerationASTConsumer>(&CI.getASTContext());
    }else {
        // 如果没有匹配到任何模式，抛出异常
        spdlog::error("Unsupported mode: {}", YokiConfig::getInstance().getMode());
        std::exit(EXIT_FAILURE);
    }
}
