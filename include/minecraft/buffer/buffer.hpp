#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>

struct BufferData
{
    size_t size;
    const float *data;
};

namespace Buffer
{
    extern unsigned int createVertexBuffer(const BufferData &buffer, const std::vector<size_t> &strides) noexcept;
}

#endif // BUFFER_HPP