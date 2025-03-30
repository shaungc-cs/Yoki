#ifndef E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8
#define E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8
#include "CheckerBase.h"
class CheckerManager{

  public:
  static CheckerManager* getInstance(){
    static CheckerManager instance;
    return &instance;
  }

  bool registerChecker(CheckerBase* checker);

  private:
    CheckerManager() = default;
    ~CheckerManager() = default;
    CheckerManager(const CheckerManager&) = delete;
    CheckerManager& operator=(const CheckerManager&) = delete;
    CheckerManager(CheckerManager&&) = delete;
    CheckerManager& operator=(CheckerManager&&) = delete;

  std::vector<CheckerBase*> checkers;
  // std::vector<CheckerItem*> checkerItems;

};


CheckerManager* checkerManager = CheckerManager::getInstance();
#endif /* E27B18B3_6DD1_45E2_BCFC_BD7AF2D2CBB8 */
