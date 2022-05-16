#ifndef CHUNKMESH_HPP
#define CHUNKMESH_HPP

#include "minecraft/mesh/blockmesh.hpp"
#include <vector>

struct ChunkMesh
{
    std::array<std::vector<float>, attributes.size()> meshAttributes; 
};


#endif // CHUNKMESH_HPP