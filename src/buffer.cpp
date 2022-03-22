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
    unsigned int createVertexBuffer(const BufferData &buffer, const std::vector<size_t> &strides) noexcept
    {
        size_t size {}, sum {};
        for (const auto &i: strides) 
            sum += i;

        unsigned int newBuffer {};
        glGenBuffers(1, &newBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_STATIC_DRAW);
        for (size_t i {}; i < strides.size(); i++)
        {
            const auto vertexAttributeIndice = i;
            const auto vertexAttributeSize = strides[i];
            const auto dataType = GL_FLOAT;
            const auto dataIsNormalized = GL_FALSE;
            const auto stride = sum * sizeof(float);
            const auto positionOffset = reinterpret_cast<void*>(size * sizeof(float));

            glVertexAttribPointer(vertexAttributeIndice, vertexAttributeSize, dataType, dataIsNormalized, stride, positionOffset);
            glEnableVertexAttribArray(i);
            size += strides[i];
        }
        return newBuffer;
    }
}