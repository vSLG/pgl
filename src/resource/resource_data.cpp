#include <sstream>

#include <resource/resource_data.hpp>

namespace pgl::res {
ResourceData::ResourceData(char *start, char *end) {
    _start = start;
    _end   = end;
    _size  = &_end - &_start;
}

std::string ResourceData::getData() {
    std::stringstream out;
    for (char *p = _start; p != _end; ++p)
        out << *p;
    return out.str();
}

int ResourceData::size() {
    return _size;
}
}; // namespace pgl::res