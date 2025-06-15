#include "YokiUTGenerationASTViositor.h"
#include "YokiConfig.h"
#include <spdlog/spdlog.h>

bool YokiUTGenerationASTViositor::VisitFunctionDecl(FunctionDecl *node) {
  // 只收集定义了的函数（有函数体的函数）
  if (!node->hasBody()) {
    spdlog::warn("Function {} does not have a body, skipping.", node->getNameAsString());
    return true; // 返回true表示继续遍历AST
  }
  // 将函数声明添加到YokiConfig中
  spdlog::debug("Adding function declaration: {}", node->getNameAsString());
  YokiConfig::getInstance().addFunctionDecl(node);
  return true; // 返回true表示继续遍历AST 
}

