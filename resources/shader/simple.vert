// SPDX-License-Identifier: LGPL-3.0-or-later

#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    outColor = color;
}