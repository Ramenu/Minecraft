#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>

struct BufferData
{
    uint32_t buffer;
    uint32_t size;
    const void* data;
    bool isStatic;
    bool isVertexBuffer;
};

namespace Buffer
{
    extern void createBuffer(BufferData& buffer);
    extern void updateBuffer(const BufferData& buffer);
}

#endif // BUFFER_HPP