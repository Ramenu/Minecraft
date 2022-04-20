#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in float aVisible;
layout (location = 4) in float aAmbient;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out float blockAmbient;

uniform mat4 view;
layout (std140, binding = 0) uniform Matrices
{
    uniform mat4 projection;
    uniform mat3 normalMatrix;
};

void main()
{
    FragPos = aPos * aVisible;
    Normal = normalMatrix * aNormal;
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    blockAmbient = aAmbient;
}