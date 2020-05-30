#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
  public:
    Shader(const char *shaderPath);
    ~Shader();

    unsigned id;

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

  private:
    void checkError(unsigned shader, std::string type);
};