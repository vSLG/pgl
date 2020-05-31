#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace ProcessingGL::Utils {
std::vector<std::string> split(const std::string &str, char delimeter);
std::string              join(const std::vector<std::string> &vec, char splitter);
} // namespace ProcessingGL::Utils