#ifndef F1729055_B7A2_4489_801D_E8E070E34152
#define F1729055_B7A2_4489_801D_E8E070E34152

#include "CheckerBase.h"
#include "CheckerUtils.h"

class MISRA_CPP2023_Rule_9_6_1 : public CheckerBase {
public:
  bool VisitGotoStmt(GotoStmt *node, ASTContext *context) override;

public:
  std::string name = "MISRA_CPP2023:Rule_9_6_1";
  std::string description = "A goto statement shall not be used";
  CheckerCategory checkerCategory = CheckerCategory::ADVISORY;
};
#endif /* F1729055_B7A2_4489_801D_E8E070E34152 */
