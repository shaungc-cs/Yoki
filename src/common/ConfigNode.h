#pragma once

#include <string>
#include <vector>

class ConfigNode {
public:
  ConfigNode(std::string programName, std::string programPath,
             std::vector<std::string> rulesVec,
             std::vector<std::string> excludePaths)
      : programName(programName), programPath(programPath), rulesVec(rulesVec),
        excludePaths(excludePaths) {}

  std::string getProgramName();
  std::string getProgramPath();
  std::vector<std::string> getRulesVec();
  std::vector<std::string> getExcludePaths();

private:
  std::string programName;
  std::string programPath;
  std::vector<std::string> rulesVec;
  std::vector<std::string> excludePaths;
};