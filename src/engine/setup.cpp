#include <engine.hpp>

using namespace pgl;

void Engine::setup() {
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

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Load vertex + color data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // How to get position data from the array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // How to get color data
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);
}