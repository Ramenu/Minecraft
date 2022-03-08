#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>

struct BufferData
{
    uint32_t buffer;
    uint32_t size;
    const float *data;
    bool isStatic;
};

namespace Buffer
{
    extern void createBuffer(BufferData &buffer) noexcept;
    extern void updateBuffer(const BufferData &buffer) noexcept;
    extern void deleteBuffer(uint32_t &buffer) noexcept;
}

#endif // BUFFER_HPP