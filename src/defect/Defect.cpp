#include "Defect.h"

std::string Defect::getDefectId() const { return defectId; }

CheckerBase *Defect::getBelongingChecker() const { return belongingChecker; }

std::string Defect::getDefectMessage() const { return defectMessage; }

clang::SourceRange Defect::getSourceRange() const { return sourceRange; }

void Defect::setDefectId(const std::string &id) { defectId = id; }

void Defect::setBelongingChecker(CheckerBase *checker) {
  belongingChecker = checker;
}

void Defect::setDefectMessage(const std::string &message) {
  defectMessage = message;
}

void Defect::setSourceRange(const clang::SourceRange &range) {
  sourceRange = range;
}
