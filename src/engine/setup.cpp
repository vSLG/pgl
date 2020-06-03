#include <glm/gtc/matrix_transform.hpp>

#include <engine.hpp>
#include <util.hpp>

using namespace pgl;

void Engine::setup() {
    debug("(Engine) Starting setup.");
    // 0-2: pos
    // 2-5: color
    // Total of 3 positions and 3 colors.
    float vertices[] = {0.5f,
                        -0.5f,
                        0.0f,
                        1.0f,
                        0.0f,
                        0.0f,
                        -0.5f,
                        -0.5f,
                        0.0f,
                        0.0f,
                        1.0f,
                        0.0f,
                        0.0f,
                        0.5f,
                        0.0f,
                        0.0f,
                        0.0f,
                        1.0f};

    unsigned vbo;

    glGenVertexArrays(1, &tempVao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(tempVao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Load vertex + color data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // How to get position data from the array
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // How to get color data
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          6 * sizeof(float),
                          (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    tempShader = new Shader();
    tempShader->addShader(Shader::spacial, Shader::vert);
    tempShader->addShader(Shader::simple, Shader::frag);
    tempShader->linkProgram();

    camera = new Camera(glm::vec2(width, height),
                        glm::vec3(0.0f, 0.0f, -1.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
}