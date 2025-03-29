#pragma once

#include <memory>
#include <string>
#include <vector>

class Config : public std::enable_shared_from_this<Config> {
public:
  Config(std::string programName, std::string programPath,
         std::vector<std::string> rulesVec,
         std::vector<std::string> excludePaths)
      : programName(programName), programPath(programPath), rulesVec(rulesVec),
        excludePaths(excludePaths) {}

  std::string getProgramName();
  std::string getProgramPath();
  std::vector<std::string> getRulesVec();
  std::vector<std::string> getExcludePaths();

  static std::shared_ptr<Config>
  loadConfigFromFile(const std::string &filePath);

private:
  std::string programName;
  std::string programPath;
  std::vector<std::string> rulesVec;
  std::vector<std::string> excludePaths;
};