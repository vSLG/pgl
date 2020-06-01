#pragma once

#include <string>

namespace ProcessingGL::Resources {
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
} // namespace ProcessingGL::Resources