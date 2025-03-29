#include "Analyse.h"
#include <clang/Tooling/CompilationDatabase.h>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>

using namespace clang::tooling;
using namespace clang;

// void Analyse::analyse(std::string &path, const std::string &file) {
//   // std::string errorMsg;
//   // auto compilationDB =
//   // clang::tooling::CompilationDatabase::loadFromDirectory(
//   //     llvm::StringRef(path), errorMsg);

//   // if (!compilationDB) {
//   //   spdlog::error("Failed to load compile_commands.json: {}", errorMsg);
//   //   return;
//   // }

//   // ClangTool Tool(*compilationDB, file);
//   // Tool.run(newFrontendActionFactory<SastDogASTFrontendAction>().get());
// }

int Analyse::getThreadSize() {
  // 获取系统的逻辑处理器数量，然后计算线程池大小
  unsigned int num_threads = std::thread::hardware_concurrency() / 2;
  // 防止除以零或零个线程
  num_threads = num_threads > 0 ? num_threads : 1;
  return num_threads;
}

void Analyse::analyse(std::shared_ptr<CompilationDatabase> compilationDB,
                      std::vector<std::string> fileVec) {

  std::vector<std::thread> workerPool;
  auto threadSize = Analyse::getThreadSize();

  for (int i = 0; i < threadSize; ++i) {
    workerPool.emplace_back(
        std::thread([&] { Analyse::doAnalyse(compilationDB, fileVec); }));
  }

  // Wait for all threads to finish their jobs.
  for (std::thread &worker : workerPool) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void Analyse::doAnalyse(std::shared_ptr<CompilationDatabase> compilationDB,
                        std::vector<std::string> fileVec) {}
