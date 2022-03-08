#include "minecraft/vertexarray.hpp"
#include "glad/glad.h"

namespace VertexArray
{
    void createVertexArray(uint32_t &vao) noexcept
    {
        glGenVertexArrays(1, &vao);
    }

    void bindVertexArray(uint32_t &vao) noexcept
    {
        glBindVertexArray(vao);
    }

    void deleteVertexArray(uint32_t &vao) noexcept
    {
        glDeleteVertexArrays(1, &vao);
    }
}
