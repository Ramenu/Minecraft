#version 330 core

out vec4 fragColor;

in vec2 grassTextureCoords;

uniform sampler2D texture1;


void main()
{
    fragColor = texture(texture1, grassTextureCoords);
}