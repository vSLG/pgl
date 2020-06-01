#pragma once

#include <resource/resource_data.hpp>
#include <shader.hpp>

namespace ProcessingGL::Resources {
enum ResourceType { RESOURCE_SHADER, RESOURCE_N };

void        initResources();
std::string getShaderCode(Shader::ShaderName name, Shader::ShaderType type);
}; // namespace ProcessingGL::Resources