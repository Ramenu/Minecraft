#ifndef MC_CHUNKMESH_HPP
#define MC_CHUNKMESH_HPP

#include "minecraft/mesh/blockmesh.hpp"
#include <vector>

struct ChunkMesh
{
    // Don't include visibility as an attribute as it will not be used in the mesh vector anyway
    std::array<std::vector<float>, ATTRIBUTES.size() - 1> meshAttributes; 
};


#endif // MC_CHUNKMESH_HPP