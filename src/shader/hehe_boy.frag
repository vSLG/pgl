#version 400 core

out vec4 fragColor;

in vec3 outColor;

void main() {
    fragColor = vec4(outColor, 1.0);
}