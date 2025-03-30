#ifndef A2845422_688D_45CF_A44B_26F847B6AE2F
#define A2845422_688D_45CF_A44B_26F847B6AE2F

class CheckerItem {
public:
    CheckerItem(std::string name, std::string description, std::string type,
                std::string level, CheckerBase* checker)
        : checkerName(name), checkerDescription(description),
          checkerType(type), checkerLevel(level), checkerBase(checker) {}

    std::string getCheckerName() const { return checkerName; }
    std::string getCheckerDescription() const { return checkerDescription; }
    std::string getCheckerType() const { return checkerType; }
    std::string getCheckerLevel() const { return checkerLevel; }
    CheckerBase* getChecker() const { return checkerBase; }
  
  private:
    std::string checkerName;
    std::string checkerDescription;
    std::string checkerType;
    std::string checkerLevel;
    CheckerBase* checkerBase;
};
#endif /* A2845422_688D_45CF_A44B_26F847B6AE2F */
