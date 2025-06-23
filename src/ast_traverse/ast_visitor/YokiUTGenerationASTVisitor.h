#ifndef B9A6BE48_F3D8_4505_810D_31AD3F9EE71B
#define B9A6BE48_F3D8_4505_810D_31AD3F9EE71B

#include <clang/AST/AST.h>
#include <clang/AST/PrettyPrinter.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <spdlog/spdlog.h>

using namespace clang;

class YokiUTGenerationASTVisitor
    : public RecursiveASTVisitor<YokiUTGenerationASTVisitor> {
public:
  explicit YokiUTGenerationASTVisitor(ASTContext *context)
      : Context(context), Policy(Context->getPrintingPolicy()) {
    // 设置打印策略以获得更详细的输出
    // Policy.PrintCanonicalTypes = true;
    // Policy.FullyQualifiedName = true;
    spdlog::info("YokiUTGenerationASTVisitor initialized.");
  }

  bool VisitFunctionDecl(FunctionDecl *node);

private:
  ASTContext *Context;
  PrintingPolicy Policy;
};

#endif /* B9A6BE48_F3D8_4505_810D_31AD3F9EE71B */
