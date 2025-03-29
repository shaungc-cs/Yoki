#pragma once
#include <clang/Tooling/CompilationDatabase.h>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

class ThreadPool {
public:
  ThreadPool(int num_threads);
  ~ThreadPool();

  void enqueue(
      std::function<void(std::shared_ptr<clang::tooling::CompilationDatabase>,
                         const std::string &)>
          f);

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;

  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop;
};
