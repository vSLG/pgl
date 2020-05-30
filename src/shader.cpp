#include <shader.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const char *shaderPath) {
    unsigned shaderTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    id                     = glCreateProgram();

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

        shaderCode = shaderStream.str().c_str();
        /* } catch (std::ifstream::failure &e) {
            // TODO
        } */

        unsigned shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        checkError(id, "shader");

        glAttachShader(id, shader);
        glLinkProgram(id);
        checkError(id, "link");

        glDeleteShader(shader);
    }
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
    int  success;
    char log[1024];

    if (type != "program") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
            glGetShaderInfoLog(shader, 1024, NULL, log);
    } else {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
            glGetProgramInfoLog(shader, 1024, NULL, log);
    }

    if (!success) {
        std::cout << "ERROR::COMPILATION_ERROR of type: " << type << "\n"
                  << log << "\n -- --------------------------------------------------- -- "
                  << std::endl;

        throw std::runtime_error("Shader compilation error.");
    }
}