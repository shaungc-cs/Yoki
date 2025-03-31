#ifndef DD43D779_114E_4540_9E76_5E38ED4204A3
#define DD43D779_114E_4540_9E76_5E38ED4204A3
#include "CheckerBase.h"
#include "clang/Tooling/Tooling.h"
#include <string>

class Defect {

private:
  std::string defectId;
  CheckerBase *belongingChecker;
  std::string defectMessage;
  clang::SourceRange sourceRange;
};
#endif /* DD43D779_114E_4540_9E76_5E38ED4204A3 */
