#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aOffset;
layout (location = 4) in float aApplyOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 anotherProjection;

out vec3 lineColors;

void main()
{
    lineColors = aColor;
    gl_Position = anotherProjection * view * model * (vec4(aPos, 1.0));
}