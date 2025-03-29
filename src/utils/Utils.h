#pragma once

#include <string>
#include <vector>

std::vector<std::string>
getFilesToBeChecked(const std::string &compileCommandDir,
                    const std::vector<std::string> &excludePaths);
