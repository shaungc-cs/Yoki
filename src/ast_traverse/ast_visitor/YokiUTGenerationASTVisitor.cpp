#include "YokiUTGenerationASTVisitor.h"
#include "YokiConfig.h"
#include <memory>
#include <spdlog/spdlog.h>

bool YokiUTGenerationASTVisitor::VisitFunctionDecl(FunctionDecl *node) {
  spdlog::info("Visiting function declaration: {}", node->getNameAsString());
  // 只收集定义了的函数（有函数体的函数）
  if (!node->hasBody()) {
    spdlog::warn("Function {} does not have a body, skipping.",
                 node->getNameAsString());
    return true; // 返回true表示继续遍历AST
  }

  auto functionDeclNode = std::make_shared<FunctionDeclNode>(
      node, context); // 创建FunctionDeclNode实例
  YokiConfig::getInstance().addFunctionDeclNode(functionDeclNode);
  spdlog::info("Collected function declaration: {}", node->getNameAsString());
  return true; // 返回true表示继续遍历AST
}
