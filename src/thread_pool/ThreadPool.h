#ifndef DB5ADE1B_7B26_4E01_B31A_D3E852276114
#define DB5ADE1B_7B26_4E01_B31A_D3E852276114
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

#endif /* DB5ADE1B_7B26_4E01_B31A_D3E852276114 */
