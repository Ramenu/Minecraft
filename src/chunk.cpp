#include "minecraft/rendering/chunk.hpp"
#include "misc/literals.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"
#include <cmath>
#include <cstdio>
#include <numeric>

static_assert(chunkHeight == chunkWidth && chunkHeight == chunkLength, "ERROR: Width, height, and length of the chunk must be equal!");


static constexpr std::array<size_t, attributes.size()> sizeOfChunkVertices {[]() consteval {
    std::array<size_t, attributes.size()> vertices {};

    for (size_t i {}; i < vertices.size(); i++)
        vertices[i] = verticesSizes[i] * chunkVolume * sizeof(float);  

    return vertices;
}()};


/**
 * Returns the block's attributes[Attribute::Position] in the 
 * layout of the vertex buffer.
 */
static inline size_t getBlockIndex(ChunkIndex index) noexcept
{
    return ((index.y * chunkHeight + index.z) + index.x * chunkLength * chunkHeight);
}


/**
 * Modifies the chunk's block located
 * at {x, y, z}. Parameters include:
 * -> The index of the block (x, y, z) must be three whole numbers
 * -> The name of the block
 * 
 * If the name of the block is an air block, the block will
 * just be rendered invisible. Otherwise, the block's texture
 * will change corresponding to the name given.
 */
void Chunk::modifyChunk(ChunkIndex chunkIndex, Block block) noexcept 
{
    const int8_t x {chunkIndex.x}, y {chunkIndex.y}, z {chunkIndex.z};
    chunk[x][y][z] = block;
    const size_t index {getBlockIndex(chunkIndex)};
    if (block.name != BlockName::Air_Block)
    {
        static constexpr auto defaultTexCoordVertices {getTextureVertices(0.0f)};

        // Start from texOffset + 1 so we can start from y coordinate (changes the block's texture)
        const size_t texOffset {index * verticesSizes[Attribute::TexCoord]};
        for (size_t i {texOffset + 1}; i < texOffset + verticesSizes[Attribute::TexCoord]; i += 2)
            chunkVertices.attributes[Attribute::TexCoord][i] = defaultTexCoordVertices[i - texOffset] + block.getTexture();
    }
    updateChunkVisibility();
    updateBuffer();

}

/**
 * Highlights the block located at (x, y, z)
 * with the ambient level given.
 */
void Chunk::highlightBlock(ChunkIndex index, float ambient) noexcept 
{
    const size_t ambientOffset {getBlockIndex(index) * verticesSizes[Attribute::Ambient]};

    for (size_t i {ambientOffset}; i < ambientOffset + verticesSizes[Attribute::Ambient]; i++)
        chunkVertices.attributes[Attribute::Ambient][i] = ambient;
    updateBuffer();
}

/**
 * Updates this chunk's vertex buffer data.
 */
void Chunk::updateBuffer() const noexcept 
{
    vertexArray.bind();
    vertexBuffer.bind();
    size_t offset {};
    for (size_t i {}; i < attributes.size(); i++)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, sizeOfChunkVertices[i], &chunkVertices.attributes[i][0]);
        offset += sizeOfChunkVertices[i];
    }
}

/**
 * Returns the visible faces of the block in
 * an array of six floats (1.0f = visible, 0.0f = not visible)
 * Checks the neighbor of each block's direction and if it
 * is out of the chunk's border OR is an air block the face
 * will be visible.
 */
std::array<float, noOfSquaresInCube> Chunk::getVisibleFaces(ChunkIndex index) const noexcept 
{
    std::array<float, noOfSquaresInCube> visibleFaces {};

    // Back face
    // NOTE: Accessing outside of array's boundaries could lead to undefined behavior. Fix this
    if (isOutOfChunk({index.x , index.y, static_cast<int8_t>(index.z - 1)}) || 
            chunk[index.x][index.y][index.z - 1].name == BlockName::Air_Block)
                visibleFaces[0] = 1.0f;

    // Front face
    if (isOutOfChunk({index.x , index.y, static_cast<int8_t>(index.z + 1)}) ||
        chunk[index.x][index.y][index.z + 1].name == BlockName::Air_Block)
            visibleFaces[1] = 1.0f;

    // Right face
    if (isOutOfChunk({static_cast<int8_t>(index.x + 1), index.y, index.z}) ||
        chunk[index.x + 1][index.y][index.z].name == BlockName::Air_Block)
            visibleFaces[2] = 1.0f;
    
    // Left face
    if (isOutOfChunk({static_cast<int8_t>(index.x - 1), index.y, index.z}) || 
        chunk[index.x - 1][index.y][index.z].name == BlockName::Air_Block)
            visibleFaces[3] = 1.0f;
    
    // Top face
    if (isOutOfChunk({index.x ,static_cast<int8_t>(index.y + 1), index.z}) ||
        chunk[index.x][index.y + 1][index.z].name == BlockName::Air_Block)
            visibleFaces[4] = 1.0f;

    // Bottom face
    if (isOutOfChunk({index.x ,static_cast<int8_t>(index.y - 1), index.z}) || 
        chunk[index.x][index.y - 1][index.z].name == BlockName::Air_Block)
            visibleFaces[5] = 1.0f;
    
    return visibleFaces;
}

/**
 * Updates the entire chunk's blocks.
 * Checks which blocks are visible to
 * the player. Should be called whenever
 * the chunk's state has changed.
 */
void Chunk::updateChunkVisibility() noexcept 
{
    static constexpr auto invisible {getVisibleBlockVertices({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})};
    chunkVertices.attributes[Attribute::Visibility].clear();
    for (int8_t x {}; x < chunkWidth; x++)
    {
        for (int8_t y {}; y < chunkHeight; y++)
        {
            for (int8_t z {}; z < chunkLength; z++)
            {
                const ChunkIndex index {ChunkIndex{x, y, z}};
                if (blockIsVisibleToPlayer(index) && chunk[x][y][z].name != BlockName::Air_Block)
                {
                    const auto visible {getVisibleBlockVertices(getVisibleFaces(index))};
                    chunkVertices.attributes[Attribute::Visibility].insert(chunkVertices.attributes[Attribute::Visibility].end(),
                                                                           std::begin(visible),
                                                                           std::end(visible));
                    continue;
                }
                chunkVertices.attributes[Attribute::Visibility].insert(chunkVertices.attributes[Attribute::Visibility].end(),
                                                                       invisible.begin(),
                                                                       invisible.end());
            }
        }
    }
}


bool Chunk::blockIsVisibleToPlayer(ChunkIndex index) const noexcept 
{
    // This means that it is on the outskirts of the chunk, which means it is visible to the player
    if (isOutOfChunk(index + 1_i8) || isOutOfChunk(index - 1_i8))
    {
        return true; 
    }
    

    // Check each block next to this block, if all of them are not air blocks then it is not visible to the player
    return  (chunk[index.x + 1_i8][index.y][index.z].name == BlockName::Air_Block ||
             chunk[index.x - 1_i8][index.y][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y + 1_i8][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y - 1_i8][index.z].name == BlockName::Air_Block ||
             chunk[index.x][index.y][index.z + 1_i8].name == BlockName::Air_Block ||
             chunk[index.x][index.y][index.z - 1_i8].name == BlockName::Air_Block);
}


/**
 * Chunk's constructor. Initializes each of the
 * vectors to the same vertices. Though, since this
 * is very expensive chunk construction should be kept
 * to a minimum and be created before the main game
 * loop. If necessary to make a new chunk in the loop,
 * do it in a seperate thread.
 */
Chunk::Chunk(BlockName firstLayer, BlockName bottomLayers) noexcept
{
    static constexpr uint8_t halfOfWidth {chunkWidth / 2}, halfOfLength {chunkLength / 2};
    static constexpr auto blockAmbientLevel {getAmbientVertices(1.5f)};
    uint8_t xU {}, yU {}, zU {};
    for (float x {}; x < halfOfWidth; x += 0.5f)
    {
        for (float y {}; y < chunkHeight; y += 1.0f)
        {
            BlockName selectedBlock {(static_cast<uint8_t>(y) == chunkHeight - 1) ? (firstLayer) : (bottomLayers)};
            for (float z {}; z < halfOfLength; z += 0.5f)
            {
                const Block block {selectedBlock};
                chunk[xU][yU][zU] = block;
                const auto pos {createCubeAt(x, y, z)};
                const auto texture {getTextureVertices(block.getTexture())};
                chunkVertices.attributes[Attribute::Position].insert(chunkVertices.attributes[Attribute::Position].end(), 
                                                                     std::begin(pos), 
                                                                     std::end(pos));
                chunkVertices.attributes[Attribute::TexCoord].insert(chunkVertices.attributes[Attribute::TexCoord].end(),
                                                                     std::begin(texture),
                                                                     std::end(texture));
                chunkVertices.attributes[Attribute::LightDirection].insert(chunkVertices.attributes[Attribute::LightDirection].end(),
                                                                           std::begin(defaultLightDirectionVertices),
                                                                           std::end(defaultLightDirectionVertices));
                chunkVertices.attributes[Attribute::Ambient].insert(chunkVertices.attributes[Attribute::Ambient].end(),
                                                                    std::begin(blockAmbientLevel),
                                                                    std::end(blockAmbientLevel));
                zU++;
            }
            zU = 0;
            yU++;
        }
        yU = 0;
        xU++;
    }
    
    // We can't update the attributes[Attribute::Visibility] in the loop prior to this call,
    // because the array's elements do not get initialized until after
    // the loop ends. 
    updateChunkVisibility();

    // Now put the data into the chunk's vertex buffer
    // -----------------------------------------------
    // First allocate enough data for the buffer to store
    vertexArray.bind();
    vertexBuffer.bind();
    static constexpr size_t totalBytes {std::accumulate(sizeOfChunkVertices.begin(), sizeOfChunkVertices.end(), 0)};
    glBufferData(GL_ARRAY_BUFFER, totalBytes, nullptr, GL_DYNAMIC_DRAW);

    // Now fill in the buffer's data
    updateBuffer();

    // Tell OpenGL what to do with the buffer's data (where the attributes are, etc).
    static constexpr auto isNormalized {GL_FALSE};
    size_t offset {};
    for (size_t i {}; i < attributes.size(); i++)
    {
        glEnableVertexArrayAttrib(vertexBuffer.getBuffer(), i);
        glVertexAttribPointer(i,
                              attributes[i], 
                              GL_FLOAT, 
                              isNormalized, 
                              attributes[i] * sizeof(float), 
                              reinterpret_cast<const void*>(offset));
        offset += sizeOfChunkVertices[i];
    }

}
