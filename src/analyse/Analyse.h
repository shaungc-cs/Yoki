#pragma once

#include <clang/Tooling/CompilationDatabase.h>
#include <memory>
#include <string>

class Analyse {
public:
  static void
  analyse(std::shared_ptr<clang::tooling::CompilationDatabase> compilationDB,
          const std::string &file);
};
