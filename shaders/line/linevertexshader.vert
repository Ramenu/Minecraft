#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
layout (std140, binding = 0) uniform Matrices
{
    uniform mat4 projection;
};

void main()
{
    gl_Position = projection * view * model * (vec4(aPos, 1.0));
}