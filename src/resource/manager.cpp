#include <SDL2/SDL_log.h>
#include <iostream>
#include <vector>

#include <resource/manager.hpp>
#include <resource/resource_data.hpp>
#include <shader.hpp>
#include <util.hpp>

#define RESOURCE_FULL(res, suffix) \
    cat(cat(_binary_resources_, res), cat(_, suffix))

#define EXTERN_RESOURCE(res, suffix) extern char RESOURCE_FULL(res, suffix)
#define DEFINE_RESOURCE(res)     \
    EXTERN_RESOURCE(res, start); \
    EXTERN_RESOURCE(res, end)
#define DEFINE_SHADER_RESOURCE(name, type) \
    DEFINE_RESOURCE(cat(cat(cat(shader_, name), _), type))

#define CREATE_RESOURCE(res, type) \
    _resources[type].push_back(    \
        ResourceData(&RESOURCE_FULL(res, start), &RESOURCE_FULL(res, end)))
#define CREATE_SHADER_RESOURCE(name, type) \
    CREATE_RESOURCE(cat(cat(cat(shader_, name), _), type), RESOURCE_SHADER)

DEFINE_SHADER_RESOURCE(simple, vert);
DEFINE_SHADER_RESOURCE(simple, frag);
DEFINE_SHADER_RESOURCE(spacial, vert);

namespace pgl::res {

std::vector<ResourceData> _resources[RESOURCE_N];

void initResources() {
    debug("(Resources) Initializing resources.");
    CREATE_SHADER_RESOURCE(simple, vert);
    CREATE_SHADER_RESOURCE(simple, frag);
    CREATE_SHADER_RESOURCE(spacial, vert);
}

std::string getShaderCode(Shader::ShaderName name, Shader::ShaderType type) {
    debug("(Resources) Getting shader code: _resources[%u][%u].",
          RESOURCE_SHADER,
          name * Shader::TYPE_N + type);
    return _resources[RESOURCE_SHADER]
        .at(name * Shader::TYPE_N + type)
        .getData();
}
}; // namespace pgl::res