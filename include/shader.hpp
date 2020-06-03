#pragma once

#include <glm/glm.hpp>
#include <set>
#include <string>

#include <glad/glad.h>

namespace pgl {
class Shader {
  public:
    enum ShaderName { simple, spacial, NAME_N };
    enum ShaderType { vert, frag, TYPE_N };
    Shader(ShaderName name);
    Shader();
    ~Shader();

    unsigned              id;
    static const unsigned glShaders[];

    void use();
    void addShader(ShaderName name, ShaderType type);
    void linkProgram();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

  private:
    void checkError(unsigned shader, std::string type);
};
} // namespace pgl