#ifndef B9A6BE48_F3D8_4505_810D_31AD3F9EE71B
#define B9A6BE48_F3D8_4505_810D_31AD3F9EE71B

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <spdlog/spdlog.h>

using namespace clang;

class YokiUTGenerationASTVisitor
    : public RecursiveASTVisitor<YokiUTGenerationASTVisitor> {
public:
  explicit YokiUTGenerationASTVisitor(ASTContext *context) : context(context) {}

  bool VisitFunctionDecl(FunctionDecl *node);

private:
  ASTContext *context;
};

#endif /* B9A6BE48_F3D8_4505_810D_31AD3F9EE71B */
