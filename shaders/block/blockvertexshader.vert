#version 460 core

#define BLOCK_ATTRIBUTES 36
#if 1
    #define TOTAL_BLOCKS 14
    #define ATLAS_WIDTH 3
    #define ATLAS_HEIGHT (TOTAL_BLOCKS - 1)

    const float xPos = 1.0 / ATLAS_WIDTH;
    const float yPos = 1.0 / ATLAS_HEIGHT;
    const float xPos_2 = (ATLAS_WIDTH - 1) * xPos;
#endif

layout (location = 0) in vec3 aPos;
layout (location = 1) in float blockID;
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
};

#if 1
const vec2[BLOCK_ATTRIBUTES] textureCoords = {
    vec2(0.0,    yPos),
    vec2(xPos,   0.0),
    vec2(xPos,   yPos),
    vec2(xPos,   0.0),
    vec2(0.0,    yPos),
    vec2(0.0,    0.0),

    vec2(0.0,    yPos),
    vec2(xPos,   yPos),
    vec2(xPos,   0.0),
    vec2(xPos,   0.0),
    vec2(0.0,    0.0),
    vec2(0.0,    yPos),
    
    vec2(xPos,   0.0),
    vec2(0.0,    yPos),
    vec2(xPos,   yPos),
    vec2(0.0,    yPos),
    vec2(xPos,   0.0),
    vec2(0.0,    0.0),

    vec2(xPos,   0.0),
    vec2(xPos,   yPos),
    vec2(0.0,    yPos),
    vec2(0.0,    yPos),
    vec2(0.0,    0.0),
    vec2(xPos,   0.0),

    vec2(xPos,   0.0),
    vec2(xPos_2, yPos),
    vec2(xPos_2, 0.0),
    vec2(xPos_2, yPos),
    vec2(xPos,   0.0),
    vec2(xPos,   yPos),

    vec2(xPos_2, yPos),
    vec2(xPos_2, 0.0),
    vec2(1.0,    yPos),
    vec2(1.0,    yPos),
    vec2(xPos_2, 0.0),
    vec2(xPos_2, 0.0)
};
#endif

const vec3[BLOCK_ATTRIBUTES] lightDirections = {
    // Back face
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),

    // Front face
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),

    // Right face
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),

    // Left face
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),
    vec3(0.0,  0.0,  -1.0),

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

const float[TOTAL_BLOCKS] textureCoordsY = {
    0.0,
    0.0769,
    0.1538,
    0.2307,
    0.3076,
    0.3846,
    0.4615,
    0.5384,
    0.6153,
    0.6923,
    0.7692,
    0.8461,
    0.9230,
    1.0
};

void main()
{
    const int attributeId = gl_VertexID % BLOCK_ATTRIBUTES;
    FragPos = aPos * aVisible;
    Normal = lightDirections[attributeId];
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = vec2(textureCoords[attributeId].x, textureCoords[attributeId].y + textureCoordsY[int(blockID) - 1]);
    blockAmbient = aAmbient;
}