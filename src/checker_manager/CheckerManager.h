#ifndef E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8
#define E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8
#include "CheckerBase.h"
class CheckerManager {

public:
  static CheckerManager *getInstance() {
    static CheckerManager instance;
    return &instance;
  }

  void setUpEnabledCheckers(std::vector<std::string> rulesVec);

  bool registerChecker(CheckerBase *checker);

#define __SAST_DOG_VISIT_NODE__(NODE)                                          \
  bool Visit##NODE(NODE *node, ASTContext *context);
#include "visit_node.inc"
#undef __SAST_DOG_VISIT_NODE__

private:
  CheckerManager() = default;
  ~CheckerManager() = default;
  CheckerManager(const CheckerManager &) = delete;
  CheckerManager &operator=(const CheckerManager &) = delete;
  CheckerManager(CheckerManager &&) = delete;
  CheckerManager &operator=(CheckerManager &&) = delete;

  std::vector<CheckerBase *> enabledCheckerVec;
};

extern CheckerManager *checkerManager;

#endif /* E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8 */
