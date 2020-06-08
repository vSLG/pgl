// SPDX-License-Identifier: LGPL-3.0-or-later

#include <iostream>
#include <stdexcept>

#include <resource/manager.hpp>
#include <shader.hpp>
#include <util.hpp>

/*
 * This class is used to create a shader program. It supports multiple different
 * shaders. The shaders are loaded from the binary embedded resources, and
 * defined by enum in shader.hpp.
 * We can create a shader in 2 ways:
 *   1. An empty Shader object: we can specify any shader we want manually and
 *      link the program when ready.
 *   2. A named Shader object: specify a shader set and the constructor will
 *      load and link shaders from specified set automatically.
 */

using namespace pgl;

// Used to get OpenGL shader type.
const unsigned Shader::glShaders[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

std::vector<Shader *> Shader::programs;

// Named Shader constructor
Shader::Shader(ShaderName name) {
    debug("(Shader) Creating named Shader object: %u.", name);

    id = glCreateProgram();

    if (id == 0)
        throw std::runtime_error("Failed to create shader program.");

    for (int type = 0; type < TYPE_N; type++)
        addShader(name, (ShaderType) type);

    linkProgram();
}

// Empty Shader constructor.
Shader::Shader() {
    debug("(Shader) Creating blank Shader object.");
    id = glCreateProgram();
}

Shader::~Shader() {
    debug("(Shader) Clearing shader %u.", id);
    glDeleteProgram(id);
}

// Attatch specified shader to shader program. Shaders are loaded from
// resources.
void Shader::addShader(ShaderName name, ShaderType type) {
    debug("(Shader) "
          "Adding shader source (%u) of type %u to program %u.",
          name,
          type,
          id);

    const char *shaderCode;
    std::string shaderResource = res::getShaderCode(name, type);
    shaderCode                 = shaderResource.c_str();

    unsigned shader = glCreateShader(glShaders[type]);
    if (shader == 0)
        throw std::runtime_error("Failed to create shader.");

    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    checkError(shader, "shader");

    glAttachShader(id, shader);
}

void Shader::linkProgram() {
    debug("(Shader) Linking shader program %u.", id);

    glLinkProgram(id);
    checkError(id, "program");
}

// Intended to be used on the pgl::Engine::update() function.
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

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(
        glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkError(unsigned shader, const std::string type) {
    debug_assert("(Shader) Checking compiling/linking errors for: %s.",
                 type.c_str());

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
        std::stringstream logStream;
        for (GLchar i : errorLog)
            logStream << i;

        error_assert("(Shader) -- "
                     "--------------------------------------------------- --");
        error_assert("(Shader) COMPILATION_ERROR of type: %s.", type.c_str());
        error_assert("(Shader) %s", logStream.str().c_str());
        error_assert("(Shader) -- "
                     "--------------------------------------------------- --");

        throw std::runtime_error("Shader compilation error.");
    }
}

void Shader::initShaders() {
    for (unsigned i = 0; i < NAME_N; i++) {
        programs.push_back(new Shader((ShaderName) i));
    }
}