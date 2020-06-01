#include <iostream>
#include <vector>

#include <resource/manager.hpp>
#include <resource/resource_data.hpp>
#include <shader.hpp>
#include <util.hpp>

#define RESOURCE_FULL(res, suffix) cat(cat(_binary_resources_, res), cat(_, suffix))

#define EXTERN_RESOURCE(res, suffix) extern char RESOURCE_FULL(res, suffix)
#define DEFINE_RESOURCE(res)     \
    EXTERN_RESOURCE(res, start); \
    EXTERN_RESOURCE(res, end)
#define DEFINE_SHADER_RESOURCE(name, type) DEFINE_RESOURCE(cat(cat(cat(shader_, name), _), type))

#define CREATE_RESOURCE(res, type) \
    _resources[type].push_back(ResourceData(&RESOURCE_FULL(res, start), &RESOURCE_FULL(res, end)))
#define CREATE_SHADER_RESOURCE(name, type) \
    CREATE_RESOURCE(cat(cat(cat(shader_, name), _), type), RESOURCE_SHADER)

DEFINE_SHADER_RESOURCE(simple, vert);
DEFINE_SHADER_RESOURCE(simple, frag);

namespace ProcessingGL::Resources {

std::vector<ResourceData> _resources[RESOURCE_N];

void initResources() {
    CREATE_SHADER_RESOURCE(simple, vert);
    CREATE_SHADER_RESOURCE(simple, frag);
}

std::string getShaderCode(Shader::ShaderName name, Shader::ShaderType type) {
    return _resources[RESOURCE_SHADER].at(name * Shader::TYPE_N + type).getData();
}
}; // namespace ProcessingGL::Resources