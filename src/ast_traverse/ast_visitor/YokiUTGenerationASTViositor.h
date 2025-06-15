#ifndef B9A6BE48_F3D8_4505_810D_31AD3F9EE71B
#define B9A6BE48_F3D8_4505_810D_31AD3F9EE71B

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <spdlog/spdlog.h>

using namespace clang;

class YokiUTGenerationASTViositor
    : public RecursiveASTVisitor<YokiUTGenerationASTViositor> {
public:
  explicit YokiUTGenerationASTViositor(ASTContext *context) : context(context) {
    // 初始化日志记录器
    spdlog::info("YokiUTGenerationASTViositor initialized.");
  }

  bool VisitFunctionDecl(FunctionDecl *node);

private:
  ASTContext *context;
};

#endif /* B9A6BE48_F3D8_4505_810D_31AD3F9EE71B */
