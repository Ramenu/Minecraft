#version 460 core

#define TOTAL_BLOCKS 15
precision lowp float;

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
layout (location = 2) in float aAmbient;
layout (location = 3) in float aVisible;

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
    vec3(0.43,  0.0,  0.0),
    vec3(0.43,  0.0,  0.0),
    vec3(0.43,  0.0,  0.0),
    vec3(0.43,  0.0,  0.0),
    vec3(0.43,  0.0,  0.0),
    vec3(0.43,  0.0,  0.0),

    // Right face
    vec3(0.1,  0.0,   0.0),
    vec3(0.1,  0.0,   0.0),
    vec3(0.1,  0.0,   0.0),
    vec3(0.1,  0.0,   0.0),
    vec3(0.1,  0.0,   0.0),
    vec3(0.1,  0.0,   0.0),

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
   0.06666666666666667, // Cobblestone Block
   0.13333333333333333, // Dirt Block
   0.2, // Stone Block
   0.26666666666666666, // Coal Ore Block
   0.3333333333333333, // Iron Ore Block
   0.4, // Gold Ore Block
   0.4666666666666667, // Redstone Ore Block
   0.5333333333333333, // Diamond Ore Block
   0.6, // Emerald Ore Block
   0.6666666666666666, // Oak Wood Block
   0.7333333333333333, // Leaf Block
   0.8, // Water Block
   0.8666666666666667, // Sand Block
   0.9333333333333333, // Cactus Block
};

void main()
{
    const int attributeId = gl_VertexID % BLOCK_ATTRIBUTES;
    const int blockFragID = int(blockID) - 1;
    FragPos = aPos * aVisible;
    Normal = lightDirections[attributeId];
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = vec2(textureCoords[attributeId].x, textureCoords[attributeId].y + textureCoordsY[blockFragID]);
    blockAmbient = aAmbient;
}