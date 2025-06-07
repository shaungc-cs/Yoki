#ifndef E32C7F65_C606_4DEE_9B24_B11CA35DAD40
#define E32C7F65_C606_4DEE_9B24_B11CA35DAD40

#include <memory>
#include <string>
#include <vector>

class SastConfig : public std::enable_shared_from_this<SastConfig> {
public:
  SastConfig(std::string programName, std::string programPath,
             std::vector<std::string> rulesVec,
             std::vector<std::string> excludePaths)
      : programName(programName), programPath(programPath), rulesVec(rulesVec),
        excludePaths(excludePaths) {}

  std::string getProgramName();
  std::string getProgramPath();
  std::vector<std::string> getRulesVec();
  std::vector<std::string> getExcludePaths();

  static std::unique_ptr<SastConfig>
  loadConfigFromFile(const std::string &filePath);

private:
  std::string programName;
  std::string programPath;
  std::vector<std::string> rulesVec;
  std::vector<std::string> excludePaths;
};

#endif /* E32C7F65_C606_4DEE_9B24_B11CA35DAD40 */
