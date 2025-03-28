#include "ConfigNode.h"

std::string ConfigNode::getProgramName() { return programName; }

std::string ConfigNode::getProgramPath() { return programPath; }

std::vector<std::string> ConfigNode::getRulesVec() { return rulesVec; }

std::vector<std::string> ConfigNode::getExcludePaths() { return excludePaths; }