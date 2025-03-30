#ifndef E0475687_9D14_462E_9FFD_DE95C636A8AB
#define E0475687_9D14_462E_9FFD_DE95C636A8AB

#define __CHECKER_CTOR__(checker_name)                                         \
  checker_name(std::string name, std::string description,                      \
               CheckerCategory category)                                       \
      : CheckerBase(name, description, category) {}

#define __REGISTER_CHECKER__(CLASS_NAME, CHECKER_NAME, DESC, CATEGORY)         \
  class CLASS_NAME##Registrar {                                                \
  public:                                                                      \
    CLASS_NAME##Registrar() {                                                  \
      CheckerManager::getInstance()->registerChecker(                          \
          new CLASS_NAME(CHECKER_NAME, DESC, CheckerCategory::CATEGORY));      \
    }                                                                          \
  };                                                                           \
  static CLASS_NAME##Registrar registrar;

enum class CheckerCategory { ADVISORY, REQUIRED, MANDATORY };

#endif /* E0475687_9D14_462E_9FFD_DE95C636A8AB */
