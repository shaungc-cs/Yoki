#ifndef C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E
#define C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E
#include "Defect.h"
#include <memory>
#include <mutex>
#include <vector>

#include "SastConfig.h"

class DefectManager {
public:
  static DefectManager *getInstance() {
    static DefectManager instance;
    return &instance;
  }

  void addDefect(const Defect &defect);

  void dumpAsJson();

  void dumpAsHtml();

  void setSastConfig(std::shared_ptr<SastConfig> config) {
    sastConfig = config;
  }

  void clearDefects() { defects.clear(); }

  int size() const { return defects.size(); }

private:
  // 禁用拷贝构造函数和赋值运算符
  DefectManager(const DefectManager &) = delete;
  DefectManager &operator=(const DefectManager &) = delete;
  DefectManager() = default;
  ~DefectManager() = default;
  std::vector<Defect> defects{1000};

  std::shared_ptr<SastConfig> sastConfig = nullptr;

  std::mutex defectMutex;
};

#endif /* C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E */
