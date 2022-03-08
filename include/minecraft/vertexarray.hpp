#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <cstdint>

namespace VertexArray
{
    extern void createVertexArray(uint32_t &vao) noexcept;
    extern void bindVertexArray(uint32_t &vao) noexcept;
    extern void deleteVertexArray(uint32_t &vao) noexcept;
}

#endif // VERTEXARRAY_HPP
