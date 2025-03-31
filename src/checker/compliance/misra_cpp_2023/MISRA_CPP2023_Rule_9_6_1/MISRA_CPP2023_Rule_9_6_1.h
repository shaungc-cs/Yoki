#ifndef F1729055_B7A2_4489_801D_E8E070E34152
#define F1729055_B7A2_4489_801D_E8E070E34152

#include "CheckerBase.h"
#include "CheckerManager.h"
#include "CheckerUtils.h"
#include "Defect.h"
#include "DefectManager.h"
#include <string>

class MISRA_CPP2023_Rule_9_6_1 : public CheckerBase {
public:
  __CHECKER_CTOR__(MISRA_CPP2023_Rule_9_6_1);

  bool VisitGotoStmt(GotoStmt *node, ASTContext *context) override;
};
__REGISTER_CHECKER__(MISRA_CPP2023_Rule_9_6_1, "MISRA_CPP:Rule 9.6.1",
                     "A goto statement shall not be used.", ADVISORY);

#endif /* F1729055_B7A2_4489_801D_E8E070E34152 */
