#ifndef F1729055_B7A2_4489_801D_E8E070E34152
#define F1729055_B7A2_4489_801D_E8E070E34152

#include "ChcekerManager.h"

class Rule_9_6_1 : public CheckerBase {
  public:
  bool VisitGotoStmt(GotoStmt *node, ASTContext *context) override;
};


static{
  checkerManager->register(new Rule_9_6_1());
}

#endif /* F1729055_B7A2_4489_801D_E8E070E34152 */
