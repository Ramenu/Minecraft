#ifndef MC_CHUNKMESH_HPP
#define MC_CHUNKMESH_HPP

#include "minecraft/mesh/blockmesh.hpp"
#include <vector>

struct ChunkMesh
{
    std::array<std::vector<float>, ATTRIBUTES.size()> meshAttributes; 
};


#endif // MC_CHUNKMESH_HPP