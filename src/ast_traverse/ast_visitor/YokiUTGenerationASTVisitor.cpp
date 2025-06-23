#include "YokiUTGenerationASTVisitor.h"
#include "YokiConfig.h"
#include <memory>
#include <spdlog/spdlog.h>

#include "clang/Basic/SourceManager.h"

#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <string>

bool YokiUTGenerationASTVisitor::VisitFunctionDecl(FunctionDecl *node) {
  spdlog::info("Visiting function declaration: {}", node->getNameAsString());
  // // 只收集定义了的函数（有函数体的函数）
  // if (!node->hasBody()) {
  //   spdlog::warn("Function {} does not have a body, skipping.",
  //                node->getNameAsString());
  //   return true; // 返回true表示继续遍历AST
  // }

  // auto functionDeclNode = std::make_shared<FunctionDeclNode>(
  //     node, Context); // 创建FunctionDeclNode实例
  // YokiConfig::getInstance().addFunctionDeclNode(functionDeclNode);
  // spdlog::info("Collected function declaration: {}",
  // node->getNameAsString());
  //     OS << "===== Function Declaration at ";

  std::error_code EC;
  std::unique_ptr<llvm::raw_fd_ostream> OSP =
      std::make_unique<llvm::raw_fd_ostream>("ast_dump.ansi", EC);
  // 打印位置信息
  auto &OS = *OSP;
  // 禁用颜色输出
  FullSourceLoc FullLocation = Context->getFullLoc(node->getBeginLoc());
  spdlog::info("FullLocation: {}", FullLocation.getSpellingLineNumber());
  if (FullLocation.isValid()) {
    OS << FullLocation.getSpellingLineNumber() << ":"
       << FullLocation.getSpellingColumnNumber() << " in "
       << FullLocation.getManager().getFilename(FullLocation).str();
  }
  OS << " =====\n\n";

  spdlog::info("Run here: {}", node->getNameAsString());
  // if (UsePrettyPrint) {
  //   // 方式1: 使用自定义格式化输出
  //   OS << "// Signature:\n";
  //   std::string TypeStr = node->getReturnType().getAsString(Policy) + " ";
  //   TypeStr += node->getNameAsString();
  //   TypeStr += "(";

  //   for (unsigned i = 0, e = node->getNumParams(); i != e; ++i) {
  //     if (i)
  //       TypeStr += ", ";
  //     TypeStr += node->getParamDecl(i)->getType().getAsString(Policy);
  //     if (node->getParamDecl(i)->getName().size())
  //       TypeStr += " " + node->getParamDecl(i)->getName().str();
  //   }

  //   TypeStr += ")";
  //   OS << TypeStr << "\n\n";

  //   // 打印限定符和存储类
  //   if (node->isInlined())
  //     OS << "inline ";
  //   if (node->isVirtualAsWritten())
  //     OS << "virtual ";
  //   if (node->isStatic())
  //     OS << "static ";
  //   if (node->isExternC())
  //     OS << "extern \"C\" ";

  //   // 打印函数体（如果有）
  //   if (node->hasBody()) {
  //     OS << "// Has body: Yes\n";
  //     // 获取函数体的源代码
  //     SourceRange Range = node->getBody()->getSourceRange();
  //     if (Range.isValid()) {
  //       SourceManager &SM = Context->getSourceManager();
  //       OS << "// Body:\n";
  //       OS << Lexer::getSourceText(CharSourceRange::getTokenRange(Range), SM,
  //                                  Context->getLangOpts())
  //                 .str()
  //          << "\n";
  //     }
  //   } else {
  //     OS << "// Has body: No\n";
  //   }

  // } else {
  // 方式2: 使用内置的dump方法
  OS << "// Raw AST Dump:\n";
  node->dump(OS);
  OS << "\n";
  // }

  OS << "\n==========================================================\n\n";
  OS.close();  // 关闭输出流
  return true; // 返回true表示继续遍历AST
}
