#include "spdlog/sinks/basic_file_sink.h"
#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <spdlog/spdlog.h>

using namespace clang;
using namespace clang::tooling;

int llvm::DisableABIBreakingChecks = 1;

class FunctionVisitor : public RecursiveASTVisitor<FunctionVisitor> {
public:
  explicit FunctionVisitor(ASTContext *Context) : Context(Context) {}

  bool VisitFunctionDecl(FunctionDecl *Declaration) {
    if (Declaration->isThisDeclarationADefinition()) {
      llvm::outs() << "Found function: "
                   << Declaration->getNameInfo().getName().getAsString()
                   << "\n";
    }
    return true;
  }

private:
  ASTContext *Context;
};

class FunctionASTConsumer : public ASTConsumer {
public:
  explicit FunctionASTConsumer(ASTContext *Context) : Visitor(Context) {}

  virtual void HandleTranslationUnit(ASTContext &Context) override {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  FunctionVisitor Visitor;
};

class FunctionFrontendAction : public ASTFrontendAction {
public:
  virtual std::unique_ptr<ASTConsumer>
  CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
    return std::make_unique<FunctionASTConsumer>(&CI.getASTContext());
  }
};

// Command line options
static llvm::cl::OptionCategory MyToolCategory("SastDog options");

int main(int argc, const char **argv) {
  llvm::cl::HideUnrelatedOptions(MyToolCategory);

  // 定义一个命令行选项，并将其归类到自定义类别中
  static llvm::cl::opt<std::string> compileCommandFilePath(
      llvm::cl::Positional, llvm::cl::desc("path to compile_command.json"),
      llvm::cl::Required, llvm::cl::cat(MyToolCategory));

  llvm::cl::ParseCommandLineOptions(argc, argv, "SastDog\n");

  spdlog::info("Path to compiler command file: " + compileCommandFilePath);

  // 设置日志级别为 info
  spdlog::set_level(spdlog::level::info);

  // auto ExpectedParser = CommonOptionsParser::create(argc, argv,
  // MyToolCategory); if (!ExpectedParser) {
  //   llvm::errs() << ExpectedParser.takeError();
  //   return 1;
  // }
  // CommonOptionsParser &OptionsParser = *ExpectedParser;

  // ClangTool Tool(OptionsParser.getCompilations(),
  //                OptionsParser.getSourcePathList());

  // return Tool.run(newFrontendActionFactory<FunctionFrontendAction>().get());
}
