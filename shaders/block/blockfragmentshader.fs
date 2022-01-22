#version 460 core

out vec4 fragColor;

in vec2 TexCoord;

uniform sampler2D allTextures;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //fragColor = vec4(lightColor * objectColor, 1.0);
    fragColor = texture(allTextures, TexCoord);
}