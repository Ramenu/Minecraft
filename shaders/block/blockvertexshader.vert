#version 460 core

#define TOTAL_BLOCKS 13
#define BLOCK_ATTRIBUTES 36
#if 1
    #define ATLAS_WIDTH 3
    #define ATLAS_HEIGHT (TOTAL_BLOCKS)

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
out float blockOpacity;

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
    vec3(0.5,  0.0,  0.0),
    vec3(0.5,  0.0,  0.0),
    vec3(0.5,  0.0,  0.0),
    vec3(0.5,  0.0,  0.0),
    vec3(0.5,  0.0,  0.0),
    vec3(0.5,  0.0,  0.0),

    // Right face
    vec3(0.0,  0.0,   1.0),
    vec3(0.0,  0.0,   1.0),
    vec3(0.0,  0.0,   1.0),
    vec3(0.0,  0.0,   1.0),
    vec3(0.0,  0.0,   1.0),
    vec3(0.0,  0.0,   1.0),

    // Left face
    vec3(0.0,  0.0,  1.0),
    vec3(0.0,  0.0,  1.0),
    vec3(0.0,  0.0,  1.0),
    vec3(0.0,  0.0,  1.0),
    vec3(0.0,  0.0,  1.0),
    vec3(0.0,  0.0,  1.0),

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
   0.0, // Grass Block
   0.07692307692307693, // Cobblestone Block
   0.15384615384615385, // Dirt Block
   0.23076923076923078, // Stone Block
   0.3076923076923077, // Coal Ore Block
   0.38461538461538464, // Iron Ore Block
   0.46153846153846156, // Gold Ore Block
   0.5384615384615384, // Redstone Ore Block
   0.6153846153846154, // Diamond Ore Block
   0.6923076923076923, // Emerald Ore Block
   0.7692307692307693, // Oak Wood Block
   0.8461538461538461, // Leaf Block
   0.9230769230769231, // Water Block
};

const float[TOTAL_BLOCKS] blockOpacities = {
   1.0, // Grass Block
   1.0, // Cobblestone Block
   1.0, // Dirt Block
   1.0, // Stone Block
   1.0, // Coal Ore Block
   1.0, // Iron Ore Block
   1.0, // Gold Ore Block
   1.0, // Redstone Ore Block
   1.0, // Diamond Ore Block
   1.0, // Emerald Ore Block
   1.0, // Oak Wood Block
   1.0, // Leaf Block
   0.8, // Water Block
};

void main()
{
    const int attributeId = gl_VertexID % BLOCK_ATTRIBUTES;
    FragPos = aPos * aVisible;
    Normal = lightDirections[attributeId];
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = vec2(textureCoords[attributeId].x, textureCoords[attributeId].y + textureCoordsY[int(blockID) - 1]);
    blockAmbient = aAmbient;
    blockOpacity = blockOpacities[int(blockID) - 1];
}