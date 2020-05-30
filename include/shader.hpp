#pragma once

#include <set>
#include <string>

#include <glad/glad.h>

class Shader {
  public:
    Shader(const std::string &shaderPath);
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