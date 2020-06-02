#pragma once

#include <sstream>
#include <string>
#include <vector>

#define xcat(a, b) a##b
#define cat(a, b)  xcat(a, b)

namespace pgl::Utils {
std::vector<std::string> split(const std::string &str, char delimeter);
std::string              join(const std::vector<std::string> &vec, char splitter);
} // namespace pgl::Utils