// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <glad/glad.h>

namespace pgl {
class Shader {
  public:
    enum ShaderName { simple, NAME_N };
    enum ShaderType { vert, frag, TYPE_N };
    Shader(ShaderName name);
    Shader();
    ~Shader();

    unsigned                     id;
    static const unsigned        glShaders[];
    static std::vector<Shader *> programs;

    static void initShaders();

    void use();
    void addShader(ShaderName name, ShaderType type);
    void linkProgram();

    // Set uniforms specified in shader sources.
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

  private:
    void checkError(unsigned shader, std::string type);
};
} // namespace pgl