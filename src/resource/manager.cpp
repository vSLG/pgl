// SPDX-License-Identifier: LGPL-3.0-or-later

#include <SDL2/SDL_log.h>
#include <iostream>
#include <vector>

#include <resource/manager.hpp>
#include <resource/resource_data.hpp>
#include <shader.hpp>
#include <util.hpp>

/******************************************************************************
 * This file is used for initializing and getting project resources.          *
 * Since we embed resources in the binary itself, we must reference them with *
 * `extern char ...`, which is a pointer. Each resource has its _start and    *
 * _end symbols pointing to where their data is, and an int _size.            *
 * For sake of readability, define them with macros.                          *
 *                                                                            *
 * TODO: Embed a file containing all resources names and define them in a     *
 * loop.                                                                      *
 ******************************************************************************/

// Don't bother understanding how it functions. It just works.
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

// Defining their 'extern char ...' symbols.
DEFINE_SHADER_RESOURCE(simple, vert);
DEFINE_SHADER_RESOURCE(simple, frag);
DEFINE_SHADER_RESOURCE(spacial, vert);

namespace pgl::res {

/*
 * We store resources in an array of vectors. Each index represents a resource
 * type (we have only shader type currently). Check pgl::res::ResourceType for
 * types supported.
 */
std::vector<ResourceData> _resources[RESOURCE_N];

// Append defined resources above into the resource store.
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

    // This will lead us an error in the future. We must change the shader type
    // selection once it starts causing us problems.
    return _resources[RESOURCE_SHADER]
        .at(name * Shader::TYPE_N + type)
        .getData();
}
}; // namespace pgl::res