#include "Rule_9_6_1.h"

  bool Rule_9_6_1::VisitGotoStmt(GotoStmt *node, ASTContext *context) {
    // defect
    spdlog::error("Rule_9_6_1: Goto statement is used in the code.");
    return true;
  }
