#pragma once

#include <clang/Tooling/CompilationDatabase.h>
#include <memory>
#include <string>
#include <vector>

using namespace clang::tooling;

class Analyse {
public:
  static int getThreadSize();
  static void analyse(std::shared_ptr<CompilationDatabase> compilationDB,
                      std::vector<std::string> fileVec);
  static void doAnalyse(std::shared_ptr<CompilationDatabase> compilationDB,
                        std::vector<std::string> fileVec);
};
