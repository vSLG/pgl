#include <sstream>

#include <resource/resource_data.hpp>

using namespace pgl::res;

ResourceData::ResourceData(char *start, char *end) {
    _start = start;
    _end   = end;
    _size  = &_end - &_start; // Wrong?
}

std::string ResourceData::getData() {
    std::stringstream out;

    // Read embedded data from _start pointer until it reaches its end.
    for (char *p = _start; p != _end; ++p)
        out << *p;
    return out.str();
}

int ResourceData::size() {
    return _size;
}