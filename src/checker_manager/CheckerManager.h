#ifndef E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8
#define E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8

#include "CheckerBase.h"
#include <memory>

class CheckerManager {
public:
  static CheckerManager &getInstance() {
    static CheckerManager instance;
    return instance;
  }

  void initializeCheckers();

  int size() const { return supportCheckerVec.size(); }

  void setUpEnabledCheckers(const std::vector<std::string> &rulesVec);

  const std::vector<std::shared_ptr<CheckerBase>> &getSupportCheckers() const {
    return supportCheckerVec;
  }
  const std::vector<std::shared_ptr<CheckerBase>> &getEnabledCheckers() const {
    return enabledCheckerVec;
  }

#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  bool Visit##NODE(NODE *node, ASTContext *context);
#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__

private:
  CheckerManager() { supportCheckerVec.reserve(1000); }
  ~CheckerManager() = default;
  CheckerManager(const CheckerManager &) = delete;
  CheckerManager &operator=(const CheckerManager &) = delete;
  CheckerManager(CheckerManager &&) = delete;
  CheckerManager &operator=(CheckerManager &&) = delete;

  std::vector<std::shared_ptr<CheckerBase>> supportCheckerVec{};
  std::vector<std::shared_ptr<CheckerBase>> enabledCheckerVec{};
};

#endif /* E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8 */
