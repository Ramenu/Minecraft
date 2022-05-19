#version 460 core

out vec4 lineFragColor;

in vec3 lineColors;

void main()
{
    lineFragColor = vec4(lineColors, 1.0);
}