#version 460 core

#define BLOCK_ATTRIBUTES (36)
#define ATTRIBUTE_ID ((gl_VertexID) % (BLOCK_ATTRIBUTES))

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aVisible;
layout (location = 3) in float aAmbient;


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

const vec3[BLOCK_ATTRIBUTES] lightDirections = {
    // Back face
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),

    // Front face
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),

    // Right face
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),

    // Left face
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),
    vec3(0.0,  0.0,  0.0),

    // Top face
    vec3(0.0,  1.0,  0.0),
    vec3(0.0,  1.0,  0.0),
    vec3(0.0,  1.0,  0.0),
    vec3(0.0,  1.0,  0.0),
    vec3(0.0,  1.0,  0.0),
    vec3(0.0,  1.0,  0.0),

    // Bottom face
    vec3(0.0, -1.0,  0.0),
    vec3(0.0, -1.0,  0.0),
    vec3(0.0, -1.0,  0.0),
    vec3(0.0, -1.0,  0.0),
    vec3(0.0, -1.0,  0.0),
    vec3(0.0, -1.0,  0.0)
};

void main()
{
    FragPos = aPos * aVisible;
    Normal = normalMatrix * lightDirections[ATTRIBUTE_ID];
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    blockAmbient = aAmbient;
}