#version 460 core

out vec4 fragColor;

in vec2 TexCoord;

uniform sampler2D allTextures;

void main()
{
    fragColor = texture(allTextures, TexCoord);
}