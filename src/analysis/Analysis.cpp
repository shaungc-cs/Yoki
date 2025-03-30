#include "Analysis.h"
#include "SastDogASTFrontendAction.h"
#include <atomic>
#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>
#include <vector>

using namespace clang::tooling;
using namespace clang;

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

  std::mutex mtx;
  int proceedFileCount = 0;

  for (int i = 0; i < threadSize; ++i) {
    workerPool.emplace_back(std::thread([&] {
      Analyse::doAnalyse(compilationDB, fileVec, mtx, proceedFileCount);
    }));
  }

  // Wait for all threads to finish their jobs.
  for (std::thread &worker : workerPool) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void Analyse::doAnalyse(std::shared_ptr<CompilationDatabase> compilationDB,
                        std::vector<std::string> fileVec, std::mutex &mtx,
                        int proceedFileCount) {
  auto allFileSize = (int)fileVec.size();

  while (true) {
    std::vector<std::string> currentFileVec;
    std::string file;
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (proceedFileCount >= allFileSize) {
        break; // No more files to process
      }
      file = fileVec[proceedFileCount++];
    }

    currentFileVec.push_back(file);

    ClangTool Tool(*compilationDB, currentFileVec);
    Tool.run(newFrontendActionFactory<SastDogASTFrontendAction>().get());
  }
}
