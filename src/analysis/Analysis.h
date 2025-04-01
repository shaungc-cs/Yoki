#ifndef A926F5EA_8E7E_448C_A128_8F0DC2A99BBE
#define A926F5EA_8E7E_448C_A128_8F0DC2A99BBE

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
                        std::vector<std::string> fileVec,
                        std::atomic<int> &proceedFileCount);
};

#endif /* A926F5EA_8E7E_448C_A128_8F0DC2A99BBE */
