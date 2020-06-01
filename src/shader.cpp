#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <resource/manager.hpp>
#include <shader.hpp>

using namespace ProcessingGL;

Shader::Shader(ShaderName name) {
    unsigned shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    id                     = glCreateProgram();

    if (id == 0)
        throw std::runtime_error("Failed to create shader program.");

    for (int type = 0; type < TYPE_N; type++) {
        const char *shaderCode;
        std::string code = Resources::getShaderCode(name, (ShaderType) type);
        shaderCode       = code.c_str();

        unsigned shader = glCreateShader(shaderTypes[type]);
        if (shader == 0)
            throw std::runtime_error("Failed to create shader.");

        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        checkError(shader, "shader");

        glAttachShader(id, shader);

        glDeleteShader(shader);
    }

    glLinkProgram(id);
    checkError(id, "program");
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::checkError(unsigned shader, const std::string type) {
    GLint               success;
    std::vector<GLchar> errorLog;

    if (type != "program") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE) {
            GLint maxLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);

            errorLog.resize(maxLen);
            glGetShaderInfoLog(shader, maxLen, &maxLen, &errorLog[0]);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success != GL_TRUE) {
            GLint maxLen = 0;
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLen);

            errorLog.resize(maxLen);
            glGetProgramInfoLog(shader, maxLen, &maxLen, &errorLog[0]);
        }
    }

    if (success != GL_TRUE) {
        std::cout << "ERROR::COMPILATION_ERROR of type: " << type << "\n";
        for (GLchar i : errorLog)
            std::cout << i;
        std::cout << " -- --------------------------------------------------- -- " << std::endl;

        throw std::runtime_error("Shader compilation error.");
    }
}