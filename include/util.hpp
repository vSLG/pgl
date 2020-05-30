#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace Utils {
std::vector<std::string> split(const std::string &str, char delimeter);
std::string              join(const std::vector<std::string> &vec, char splitter);
} // namespace Utils