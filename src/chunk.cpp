#include "minecraft/rendering/chunk.hpp"
#include "misc/literals.hpp"
#include "minecraft/camera/camera.hpp"
#include "minecraft/math/glmath.hpp"
#include "minecraft/audio/sound.hpp"
#include "minecraft/rendering/renderer.hpp"
#include "minecraft/window/window.hpp"
#include "minecraft/world/worldgen.hpp"
#include "GLFW/glfw3.h"
#include <cmath>
#include <cstdio>
#include <numeric>
#include <algorithm>

static constexpr bool CHECK_BOUNDS_ACCESS {true}; // use for debug builds only

#define ABORT_ON_OF_BOUNDS_ACCESS(index) \
    if constexpr (CHECK_BOUNDS_ACCESS) { \
        if (isOutOfChunk(index)) \
        { \
            printf("ERROR: At %s, index is {%f, %f, %f}!\n", __func__,static_cast<double>(index.x), static_cast<double>(index.y), static_cast<double>(index.z)); \
            exit(EXIT_FAILURE); \
        } \
    }
    

static constexpr auto INVISIBLE_VERTICES {getVisibleBlockVertices({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f})};
static constexpr float DEFAULT_AMBIENT_LEVEL {1.5f};
static constexpr float COMPLETELY_VISIBLE {1.0f};

static constexpr std::array<std::size_t, ATTRIBUTES.size()> SIZE_OF_CHUNK_VERTICES {[](){
    std::array<std::size_t, ATTRIBUTES.size()> vertices {};

    for (std::size_t i {}; i < vertices.size(); ++i)
        vertices[i] = verticesSizes[i] * CHUNK_VOLUME * sizeof(float);  

    return vertices;
}()};

static constexpr std::array<std::size_t, ATTRIBUTES.size()> OFFSETS {[](){
    std::array<std::size_t, ATTRIBUTES.size()> attributeOffsets {};
    std::size_t offset {};
    for (std::size_t i {}; i < SIZE_OF_CHUNK_VERTICES.size(); ++i)
    {
        attributeOffsets[i] = offset;
        offset += SIZE_OF_CHUNK_VERTICES[i];
    }
    return attributeOffsets;
}()};

static constexpr std::size_t TOTAL_BYTES {std::accumulate(SIZE_OF_CHUNK_VERTICES.begin(), SIZE_OF_CHUNK_VERTICES.end(), 0)};

/**
 * Returns a single index (from 0 to 'CHUNKVOLUME') 
 * based on a three dimensional
 * array index.
 */
static inline constexpr std::size_t getBlockIndex(glm::i8vec3 index) noexcept {
    return ((index.y * CHUNK_HEIGHT + index.z) + index.x * CHUNK_LENGTH * CHUNK_HEIGHT);
}


/**
 * The index that should be passed should be the indice of the block
 * that surround the block's face you want to check. For example, if
 * you want to check if the bottom face of a block is visible, pass the
 * indice bottom to the block's chunk index (so y - 1). Returns true if
 * the face is visible.
 */
constexpr bool Chunk::faceIsVisible(glm::i8vec3 index) const noexcept {
    if (isOutOfChunk(index))
        return true;
    return (chunk[index.x][index.y][index.z].name == Air_Block || chunk[index.x][index.y][index.z].name == Water_Block);
}


void Chunk::drawChunk() const noexcept
{
    static constexpr std::size_t FIRST {0}, COUNT {CUBE_ATTRIBUTES * CHUNK_VOLUME};
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, FIRST, COUNT - FIRST);
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
void Chunk::modifyChunk(glm::i8vec3 index, Block block) noexcept 
{
    ABORT_ON_OF_BOUNDS_ACCESS(index)
    const std::int32_t x {index.x}, y {index.y}, z {index.z};
    chunk[x][y][z] = block;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    if (block.name != Air_Block)
    {
        const std::size_t bufferOffset {getBlockIndex(index)};
        updateBuffer(bufferOffset, Attribute::BlockID, getBlockIDVertices(block.name));
    }

    // We have to update the blocks surrounding the block that was modified only for performance
    updateChunkVisibility(index);
}

/**
 * Updates the state of the blocks.
 * (which blocks are to be highlighted, 
 * which have been destroyed, or placed, etc).
 * It is recommended that this method be used
 * for the active chunk only for performance.
 * 
 * Returns true if the state of the chunk changed.
 * For the state of the chunk to be considered
 * changed, either:
 * -> A block must have been placed
 * -> A block must have been destroyed
 */
bool Chunk::updateChunk() noexcept 
{
    bool updateNeeded {};
    static constexpr float HIGHLIGHTED_AMBIENT_LEVEL {1.9f};
    for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
    {
        for (std::int32_t y {}; y < CHUNK_HEIGHT; ++y)
        {
            for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
            {
                // Not necessary to check if the player is looking at an air block
                if (blockStates[x][y][z] != None)
                {
                    const bool rayLookingAtBlock {static_cast<std::int32_t>(Camera::getCameraRay().getRay().x) % CHUNK_WIDTH == x && 
                                                  static_cast<std::int32_t>(Camera::getCameraRay().getRay().y) % CHUNK_HEIGHT == y && 
                                                  static_cast<std::int32_t>(Camera::getCameraRay().getRay().z) % CHUNK_LENGTH == z};

                    // If the block is highlighted check to see if its still being looked at by the player
                    static constexpr BlockState HIGHLIGHTED_AND_VISIBLE {Highlighted|Visible};
                    if (blockStates[x][y][z] == HIGHLIGHTED_AND_VISIBLE)
                    {
                        const glm::i8vec3 index {x, y, z};
                        if (!rayLookingAtBlock)
                        {
                            blockStates[x][y][z] &= Highlighted;
                            highlightBlock(index, DEFAULT_AMBIENT_LEVEL); // un-highlight the block
                        }
                        // Destroy the block if the left mouse button is clicked
                        if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                        {
                            Sound::playBlockBreakSound(chunk[x][y][z].name);
                            modifyChunk(index, Block{Air_Block});
                            if (isOutOfChunk(index + 1_i8) || isOutOfChunk(index - 1_i8))
                                updateNeeded = true;
                        }

                        // Place a block if the right mouse button is clicked
                        static constinit int oldState {GLFW_RELEASE};
                        const int newState {glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT)};
                        if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
                        {
                            const glm::vec3 blockDirection {-getDirectionVector(GLMath::getDirectionClosestTo(Camera::direction.front))};
                            const glm::i32vec3 blockPosition {x + blockDirection.x, y + blockDirection.y, z + blockDirection.z};

                            // Make sure that the player is not placing a block outside of the chunk's boundaries and that it is being
                            // placed on an air block
                            if (!isOutOfChunk(blockPosition) && chunk[blockPosition.x][blockPosition.y][blockPosition.z].name == Air_Block)
                            {
                                modifyChunk(blockPosition, Block{Water_Block});
                                // Highlighting it is necessary, so in the next call the method can decide whether to still keep
                                // it highlighted or not. Otherwise, the highlighted ambient will stay on it.
                                blockStates[blockPosition.x][blockPosition.y][blockPosition.z] = HIGHLIGHTED_AND_VISIBLE;
                                Sound::playBlockPlacementSound(chunk[blockPosition.x][blockPosition.y][blockPosition.z].name);
                                if (isOutOfChunk(index + 1_i8) || isOutOfChunk(index - 1_i8))
                                    updateNeeded = true;
                            }
                        }
                        oldState = newState;
                        continue;
                    }
                    if (rayLookingAtBlock)
                    {
                        blockStates[x][y][z] = HIGHLIGHTED_AND_VISIBLE;
                        const glm::i8vec3 index {x, y, z};
                        highlightBlock(index, HIGHLIGHTED_AMBIENT_LEVEL); // highlight the block
                    }
                }
            }
        }
    }
    return updateNeeded;
}

/**
 * Highlights the block located at (x, y, z)
 * with the ambient level given.
 */
void Chunk::highlightBlock(glm::i8vec3 index, float ambient) const noexcept 
{
    ABORT_ON_OF_BOUNDS_ACCESS(index)
    const std::size_t bufferIndex {getBlockIndex(index)};
    const auto vertices {getAmbientVertices(ambient)}; 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    updateBuffer(bufferIndex, Attribute::Ambient, vertices);
}

/**
 * Updates the chunk's visibility,
 * but only the blocks surrounding {x, y, z} 
 * (the index passed).
 * 
 * This method should be preferred over the other
 * overloaded one, as it only modifies the 
 * visibility of, at most, six blocks, whereas
 * the other will modify the entire chunk's
 * visibility. However, I didn't notice a
 * significant performance difference between 
 * the two.
 */
void Chunk::updateChunkVisibility(glm::i8vec3 index) noexcept
{
    ABORT_ON_OF_BOUNDS_ACCESS(index)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    const auto adjacentBlocks {getBlocksSurrounding(index)};
    for (const auto&blockCoords: adjacentBlocks)
    {
        if (blockCoords) // Make sure it is a valid coordinate
        {
            const std::size_t bufferIndex {getBlockIndex(blockCoords.value())};
            const std::int32_t x {blockCoords.value().x},
                               y {blockCoords.value().y},
                               z {blockCoords.value().z};
            if (blockIsVisibleToPlayer(blockCoords.value()) && chunk[x][y][z].name != Air_Block)
            {
                const auto visibleFaces {getVisibleFaces(blockCoords.value())};
                const auto visibleVertices {getVisibleBlockVertices(visibleFaces)};
                updateBuffer(bufferIndex, Attribute::Visibility, visibleVertices);
                blockStates[x][y][z] = Visible;
                continue;
            }
            blockStates[x][y][z] = None;
            updateBuffer(bufferIndex, Attribute::Visibility, INVISIBLE_VERTICES);
        }
    }

    // Update this block's visibility
    std::array<float, CUBE_ATTRIBUTES> visibilityVertices;
    if (chunk[index.x][index.y][index.z].name != Air_Block && blockIsVisibleToPlayer(index))
    {
        visibilityVertices = getVisibleBlockVertices(getVisibleFaces(index));
        blockStates[index.x][index.y][index.z] |= Visible;
    } 
    else
    {
        visibilityVertices = INVISIBLE_VERTICES;
        blockStates[index.x][index.y][index.z] = None;
    }
    updateBuffer(getBlockIndex(index), Attribute::Visibility, visibilityVertices);
}

/**
 * Returns an array of 6 3-dimensional
 * vectors. Each one representing a
 * block that may be adjacent to the
 * block located at {x, y, z}. 
 */
std::array<std::optional<glm::i8vec3>, SQUARES_ON_CUBE> Chunk::getBlocksSurrounding(glm::i8vec3 index) noexcept
{
    ABORT_ON_OF_BOUNDS_ACCESS(index)
    const glm::i8vec3 blockAtBack {index.x, index.y, index.z - 1_i8},
                      blockAtFront {index.x, index.y, index.z + 1_i8},
                      blockAtRight {index.x - 1_i8, index.y, index.z},
                      blockAtLeft {index.x + 1_i8, index.y, index.z},
                      blockAtTop {index.x, index.y + 1_i8, index.z},
                      blockAtBottom {index.x, index.y - 1_i8, index.z};

    // Check if the block is not on the borders, if so then it makes life much easier for us and all blocks
    // adjacent to it can be returned.
    if (!isOutOfChunk(index + 1_i8) && !isOutOfChunk(index - 1_i8)) 
    {
        return {
            std::optional{blockAtBack},
            std::optional{blockAtFront},
            std::optional{blockAtRight},
            std::optional{blockAtLeft},
            std::optional{blockAtTop},
            std::optional{blockAtBottom}
        };
    }

    const glm::i8vec3 adjacentBlocks[SQUARES_ON_CUBE] {
        blockAtBack,
        blockAtFront,
        blockAtRight,
        blockAtLeft,
        blockAtTop,
        blockAtBottom
    };

    std::array<std::optional<glm::i8vec3>, SQUARES_ON_CUBE> surroundingBlocks {
        std::nullopt, std::nullopt, std::nullopt,
        std::nullopt, std::nullopt, std::nullopt
    };

    for (std::size_t i {}; i < surroundingBlocks.size(); ++i)
        if (!isOutOfChunk(adjacentBlocks[i]))
            surroundingBlocks[i] = adjacentBlocks[i];
    return surroundingBlocks;
}

void Chunk::updateChunkVisibilityToNeighbor(const std::array<std::array<std::array<Block, CHUNK_LENGTH>, CHUNK_HEIGHT>, CHUNK_WIDTH> &chunkNeighbor, 
                                            Face face) const noexcept 
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    std::int32_t begin {0}, end {CHUNK_HEIGHT - 1};
    if (face == FrontFace || face == RightFace || face == TopFace)
        std::swap(begin, end);
    for (std::int32_t a {}; a < CHUNK_WIDTH; ++a)
    {
        for (std::int32_t v {}; v < CHUNK_HEIGHT; ++v)
        {
            glm::i8vec3 index;
            float visibleLevel {};
            if (face == FrontFace || face == BackFace) // Check faces on Z
            {
                index = {a, v, begin};
                if (chunk[a][v][begin].name != Air_Block && chunkNeighbor[a][v][end].name == Air_Block)
                    visibleLevel = COMPLETELY_VISIBLE;
            }
            else if (face == TopFace || face == BottomFace) // Check faces on Y
            {
                index = {a, begin, v};
                if (chunk[a][begin][v].name != Air_Block && chunkNeighbor[a][end][v].name == Air_Block)
                    visibleLevel = COMPLETELY_VISIBLE;
            }
            else // Check faces on X
            {
                index = {begin, v, a};
                if (chunk[begin][v][a].name != Air_Block && chunkNeighbor[end][v][a].name == Air_Block)
                    visibleLevel = COMPLETELY_VISIBLE;
            }

            const std::size_t blockOffset {getBlockIndex(index)};
            const float visibleFaces[] {visibleLevel, visibleLevel, visibleLevel, visibleLevel, visibleLevel, visibleLevel};
            updateBuffer(blockOffset, Attribute::Visibility, visibleFaces, face);
        }
    }
}



/**
 * Updates a region of the buffer's data, given
 * the attribute index. Requires that the
 * vertex buffer be binded before this is called!
 */
void Chunk::updateBuffer(std::size_t bufferIndex, Attribute attributeIndex, std::span<const float> vertices, Face face) noexcept
{
    const std::size_t bufferOffset {(bufferIndex * verticesSizes[attributeIndex] * sizeof(float) + OFFSETS[attributeIndex])
                                + face * SQUARES_ON_CUBE * sizeof(float)};
    const std::size_t offsetEnd {vertices.size() * sizeof(float)};;

    glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, offsetEnd, vertices.data());
}

/**
 * Returns true if any of the
 * faces are visible.
 */
static inline constexpr bool anyFacesAreVisible(const std::array<float, SQUARES_ON_CUBE> &faces) 
{
    return (std::any_of(faces.begin(), faces.end(), [](auto face) {
        return face >= COMPLETELY_VISIBLE;
    }));
}

/**
 * Returns the visible faces of the block in
 * an array of six floats (1.0f = visible, 0.0f = not visible)
 * Checks the neighbor of each block's direction and if it
 * is out of the chunk's border OR is an air block the face
 * will be visible.
 */
constexpr std::array<float, SQUARES_ON_CUBE> 
Chunk::getVisibleFaces(glm::i8vec3 index) const noexcept 
{
    ABORT_ON_OF_BOUNDS_ACCESS(index);
    std::array<float, SQUARES_ON_CUBE> visibleFaces {};

    // Back face
    if (faceIsVisible({index.x, index.y, index.z - 1}))
            visibleFaces[Face::BackFace] = COMPLETELY_VISIBLE;

    // Front face
    if (faceIsVisible({index.x, index.y, index.z + 1}))
            visibleFaces[Face::FrontFace] = COMPLETELY_VISIBLE;

    // Right face
    if (faceIsVisible({index.x + 1, index.y, index.z}))
            visibleFaces[Face::RightFace] = COMPLETELY_VISIBLE;
    
    // Left face
    if (faceIsVisible({index.x - 1, index.y, index.z}))
            visibleFaces[Face::LeftFace] = COMPLETELY_VISIBLE;
    
    // Top face
    if (faceIsVisible({index.x, index.y + 1, index.z}))
            visibleFaces[Face::TopFace] = COMPLETELY_VISIBLE;

    // Bottom face
    if (faceIsVisible({index.x, index.y - 1, index.z}))
            visibleFaces[Face::BottomFace] = COMPLETELY_VISIBLE;
    
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
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    std::vector<float> visibleAttributes {}; 
    for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
    {
        for (std::int32_t y {}; y < CHUNK_HEIGHT; ++y)
        {
            for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
            {
                const glm::i8vec3 index {x, y, z};
                if (blockIsVisibleToPlayer(index) && chunk[x][y][z].name != Air_Block)
                {
                    const auto visibleFaces {getVisibleFaces(index)};
                    const auto visible {getVisibleBlockVertices(visibleFaces)};
                    visibleAttributes.insert(visibleAttributes.end(), visible.begin(), visible.end()); 
                    blockStates[x][y][z] |= Visible;
                    continue;
                }
                blockStates[x][y][z] = None;
                visibleAttributes.insert(visibleAttributes.end(), INVISIBLE_VERTICES.begin(), INVISIBLE_VERTICES.end());
            }
        }
    }
    glBufferSubData(GL_ARRAY_BUFFER, 
                    OFFSETS[Attribute::Visibility], 
                    SIZE_OF_CHUNK_VERTICES[Attribute::Visibility], 
    // cppcheck-suppress containerOutOfBounds ; needed otherwise it gives a false positive
                    &visibleAttributes[0]);
}


bool Chunk::blockIsVisibleToPlayer(glm::i8vec3 index) const noexcept 
{
    ABORT_ON_OF_BOUNDS_ACCESS(index)
    // This means that it is on the outskirts of the chunk, which means it is visible to the player
    if (isOutOfChunk(index + 1_i8) || isOutOfChunk(index - 1_i8))
        return true; 
    

    // Check each block next to this block, if all of them are not air/water blocks then it is not visible to the player
    return  ((chunk[index.x + 1_i8][index.y][index.z].name == Air_Block || chunk[index.x + 1_i8][index.y][index.z].name == Water_Block) ||
             (chunk[index.x - 1_i8][index.y][index.z].name == Air_Block || chunk[index.x - 1_i8][index.y][index.z].name == Water_Block) ||
             (chunk[index.x][index.y + 1_i8][index.z].name == Air_Block || chunk[index.x][index.y + 1_i8][index.z].name == Water_Block) ||
             (chunk[index.x][index.y - 1_i8][index.z].name == Air_Block || chunk[index.x][index.y - 1_i8][index.z].name == Water_Block) ||
             (chunk[index.x][index.y][index.z + 1_i8].name == Air_Block || chunk[index.x][index.y][index.z + 1_i8].name == Water_Block) ||
             (chunk[index.x][index.y][index.z - 1_i8].name == Air_Block || chunk[index.x][index.y][index.z - 1_i8].name == Water_Block));
}

/**
 * Returns true if the player is facing the chunk's
 * direction.
 */
bool Chunk::isFacingChunk(const glm::i32vec3 &chunkPos) noexcept 
{
    static constexpr float MINIMUM_ANGLE_TO_SEE {-0.36f};
    bool facingChunk {true};
    if (Camera::cameraPos.x - chunkPos.x > CHUNK_WIDTH)
        facingChunk = (glm::dot(Camera::direction.front, glm::vec3{-1.0f, 0.0f, 0.0f}) >= MINIMUM_ANGLE_TO_SEE);
    else if (Camera::cameraPos.x - chunkPos.x < -CHUNK_WIDTH)
        facingChunk = (glm::dot(Camera::direction.front, glm::vec3{1.0f, 0.0f, 0.0f}) >= MINIMUM_ANGLE_TO_SEE);
    
    if (!facingChunk) // No point to continue checking if 'facingChunk' was already set to false
        return false;

    if (Camera::cameraPos.z - chunkPos.z > CHUNK_LENGTH)
        facingChunk = (glm::dot(Camera::direction.front, glm::vec3{0.0f, 0.0f, -1.0f}) >= MINIMUM_ANGLE_TO_SEE);
    else if (Camera::cameraPos.z - chunkPos.z < -CHUNK_LENGTH)
        facingChunk = (glm::dot(Camera::direction.front, glm::vec3{0.0f, 0.0f, 1.0f}) >= MINIMUM_ANGLE_TO_SEE);
    return facingChunk;
}


/**
 * 
 * NOTE: This cannot be done in the constructor,
 * because of weird semantics happening with the vertex
 * array and buffer. This causes both of them to be
 * invalid and not work as intended. I'm not sure
 * what this reason of this is, possibly a copy
 * gets created?
 * 
 * 
 * Chunk's initialization method. Initializes each of the
 * vectors to the same vertices. Though, since this
 * is very expensive chunk construction should be kept
 * to a minimum and be created before the main game
 * loop. If necessary to make a new chunk in the loop,
 * do it in a seperate thread.
 */
void Chunk::initChunk(glm::vec3 position) noexcept 
{
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    ChunkMesh chunkVertices;
    static constexpr auto DEFAULT_BLOCK_AMBIENT_VERTICES {getAmbientVertices(DEFAULT_AMBIENT_LEVEL)};
	chunk = WorldGen::generateTerrain(WorldGen::Biome::Plains);
    position = {position.x * CHUNK_WIDTH, position.y * CHUNK_HEIGHT, position.z * CHUNK_LENGTH};

    for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
    {
        for (std::int32_t y {}; y < CHUNK_HEIGHT; ++y)
        {
            for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
            {
                const auto pos {createCubeAt(x + position.x, y + position.y, z + position.z)};
                const auto blockId {getBlockIDVertices(chunk[x][y][z].name)};
                chunkVertices.meshAttributes[Attribute::Position].insert(chunkVertices.meshAttributes[Attribute::Position].end(), 
                                                                         pos.begin(), 
                                                                         pos.end());
                
                chunkVertices.meshAttributes[Attribute::BlockID].insert(chunkVertices.meshAttributes[Attribute::BlockID].end(),
                                                                        blockId.begin(),
                                                                        blockId.end());

                chunkVertices.meshAttributes[Attribute::Ambient].insert(chunkVertices.meshAttributes[Attribute::Ambient].end(),
                                                                        DEFAULT_BLOCK_AMBIENT_VERTICES.begin(),
                                                                        DEFAULT_BLOCK_AMBIENT_VERTICES.end());
            }
        }
    }

    // Now put the data into the chunk's vertex buffer
    // -----------------------------------------------
    // First allocate enough data for the buffer to store

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, TOTAL_BYTES, nullptr, GL_DYNAMIC_DRAW);

    // Now fill in the buffer's data
    for (std::size_t i {}; i < ATTRIBUTES.size(); ++i)
        glBufferSubData(GL_ARRAY_BUFFER, OFFSETS[i], SIZE_OF_CHUNK_VERTICES[i], &chunkVertices.meshAttributes[i][0]);
    updateChunkVisibility();

    // Tell OpenGL what to do with the buffer's data (where the ATTRIBUTES are, etc).
    static constexpr int NORMALIZED_ATTRIBUTES[] {GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE};
    for (std::size_t i {}; i < ATTRIBUTES.size(); ++i)
    {
        glEnableVertexArrayAttrib(vertexBuffer, i);
        glVertexAttribPointer(i,
                              ATTRIBUTES[i], 
                              GL_FLOAT, 
                              NORMALIZED_ATTRIBUTES[i], 
                              0, // values are understood to be tightly-packed in array
                              reinterpret_cast<const void*>(OFFSETS[i]));
    }

}
