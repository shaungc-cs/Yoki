#ifndef A926F5EA_8E7E_448C_A128_8F0DC2A99BBE
#define A926F5EA_8E7E_448C_A128_8F0DC2A99BBE

#include <clang/Tooling/CompilationDatabase.h>
#include <memory>
#include <string>
#include <vector>

class Analyse {
public:
  static int getThreadSize();

  static void
  analyse(std::shared_ptr<clang::tooling::CompilationDatabase> compilationDB,
          const std::vector<std::string> &fileVec);

  static void analyse(); // 从YokiConfig获取参数的无参数版本

  static void doAnalyse(std::atomic<int> &proceedFileCount);
};

#endif /* A926F5EA_8E7E_448C_A128_8F0DC2A99BBE */
