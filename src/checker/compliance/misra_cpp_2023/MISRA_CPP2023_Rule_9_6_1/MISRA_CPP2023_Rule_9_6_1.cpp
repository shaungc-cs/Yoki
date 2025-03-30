#include "MISRA_CPP2023_Rule_9_6_1.h"

bool MISRA_CPP2023_Rule_9_6_1::VisitGotoStmt(GotoStmt *node,
                                             ASTContext *context) {
  getName();
  // defect
  return true;
}
