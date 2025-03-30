#include "CheckerManager.h"

bool CheckerManager::registerChecker(CheckerBase* checker) {
  if (checker) {
    checkers.push_back(checker);
    return true;
  }
  return false;
}
