#pragma once

#include <set>
#include <string>

#include <glad/glad.h>

namespace ProcessingGL {
class Shader {
  public:
    enum ShaderName { simple, NAME_N };
    enum ShaderType { vert, frag, TYPE_N };
    Shader(ShaderName name);
    ~Shader();

    unsigned id;

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    static const std::set<std::string> supportedShaderExt;

  private:
    void checkError(unsigned shader, std::string type);
};
} // namespace ProcessingGL