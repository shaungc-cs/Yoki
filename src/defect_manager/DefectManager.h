#ifndef C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E
#define C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E
#include "Defect.h"
#include <memory>
#include <mutex>
#include <vector>

#include "YokiConfig.h"

class DefectManager {
public:
  static DefectManager &getInstance() {
    static DefectManager instance;
    return instance;
  }

  void addDefect(const Defect &defect);

  void dumpAsJson();

  void dumpAsHtml();

  void setSastConfig(std::unique_ptr<YokiConfig> &&config) {
    // 由于YokiConfig现在是单例模式，不再需要存储副本
    // 这个方法保留是为了兼容性，但实际上什么都不做
  }

  int size() const { return defects.size(); }

private:
  // 禁用拷贝构造函数和赋值运算符
  DefectManager(const DefectManager &) = delete;
  DefectManager &operator=(const DefectManager &) = delete;
  DefectManager() { defects.reserve(1000); }
  ~DefectManager() = default;
  
  // 辅助方法
  std::string escapeHtml(const std::string& text) const;
  std::string getUniqueFileCount() const;
  std::string getCurrentWorkingDirectory() const;
  
  std::vector<Defect> defects;

  std::mutex defectMutex;
};

#endif /* C2BDBA7D_F7A1_40EE_8204_DF629E3FB04E */
