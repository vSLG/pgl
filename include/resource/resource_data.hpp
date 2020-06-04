#pragma once

#include <string>

namespace pgl::res {

// This class is used to represent a single resource in our model.
class ResourceData {
  public:
    ResourceData(char *start, char *end);

    std::string getData();
    int         size();

  private:
    char *_end;
    char *_start;
    int   _size;
};
} // namespace pgl::res