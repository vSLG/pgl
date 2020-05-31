#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <shader.hpp>

const std::set<std::string> Shader::supportedShaderExt = {"frag", "vert"};

Shader::Shader(const std::string &shaderPath) {
    unsigned shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    id                     = glCreateProgram();

    if (id == 0)
        throw std::runtime_error("Failed to create shader program.");

    for (unsigned type : shaderTypes) {
        const char *  shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        // try {
        std::stringstream shaderStream;

        switch (type) {
            case GL_FRAGMENT_SHADER:
                shaderFile.open(std::string(shaderPath) + ".frag");
                break;
            case GL_VERTEX_SHADER:
                shaderFile.open(std::string(shaderPath) + ".vert");
                break;
        }

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        std::string shaderString = shaderStream.str();
        shaderCode               = shaderString.c_str();
        /* } catch (std::ifstream::failure &e) {
            // TODO
        } */

        // printf("--------------------------------------------\ntype: %x\n%s\n", type, shaderCode);

        unsigned shader = glCreateShader(type);
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