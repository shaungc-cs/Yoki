#ifndef DD43D779_114E_4540_9E76_5E38ED4204A3
#define DD43D779_114E_4540_9E76_5E38ED4204A3
#include "CheckerBase.h"
#include <clang/Basic/SourceLocation.h>
#include <string>

class Defect {
public:
  Defect() = default;
  Defect(std::string id, CheckerBase *checker, std::string message,
         clang::SourceRange range)
      : defectId(id), belongingChecker(checker), defectMessage(message),
        sourceRange(range) {}

  std::string getDefectId() const;
  CheckerBase *getBelongingChecker() const;
  std::string getDefectMessage() const;
  clang::SourceRange getSourceRange() const;
  void setDefectId(const std::string &id);
  void setBelongingChecker(CheckerBase *checker);
  void setDefectMessage(const std::string &message);
  void setSourceRange(const clang::SourceRange &range);

private:
  std::string defectId;
  CheckerBase *belongingChecker;
  std::string defectMessage;
  clang::SourceRange sourceRange;
};
#endif /* DD43D779_114E_4540_9E76_5E38ED4204A3 */
