#include "glad/glad.h"
#include "minecraft/buffer/buffer.hpp"


namespace Buffer
{
    /**
     * Creates a new vertex buffer with
     * the given buffer data and configures
     * the attributes with the stride of each
     * attribute given. 
     * NOTE: This function enables all attributes at once.
     */
    unsigned int createVertexBuffer(BufferData &buffer, const std::vector<size_t> &strides) noexcept
    {
        size_t size {}, sum {};
        for (const auto &i: strides) sum += i;

        unsigned int newBuffer {};
        glGenBuffers(1, &newBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_STATIC_DRAW);
        for (size_t i {}; i < strides.size(); i++)
        {
            glVertexAttribPointer(i, strides[i], GL_FLOAT, GL_FALSE, sum * sizeof(float), reinterpret_cast<void*>(size * sizeof(float)));
            glEnableVertexAttribArray(i);
            size += strides[i];
        }
        return newBuffer;
    }
}