#include <util.hpp>

namespace pgl::Utils {
std::vector<std::string> split(const std::string &str, char delimeter) {
    std::vector<std::string> parts;
    std::string              part;
    std::stringstream        partStream(str);

    while (std::getline(partStream, part, delimeter))
        parts.push_back(part);

    return parts;
}

std::string join(const std::vector<std::string> &vec, char splitter) {
    std::stringstream sstr;

    for (std::string part : vec) {
        sstr << part;
        if (part != *std::prev(vec.end()))
            sstr << splitter;
    }

    return sstr.str();
}
} // namespace pgl::Utils