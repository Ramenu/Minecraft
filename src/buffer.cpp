#include "glad/glad.h"
#include "minecraft/buffer.hpp"

namespace Buffer
{
    /** 
     * Loads the data into the buffer passed. 
     * Should be called during the initialization of a buffer object only. 
     * Buffer MUST be a vertex buffer.
     */
    void createBuffer(BufferData &buffer) noexcept
    {
        const int draw = (buffer.isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glGenBuffers(1, &buffer.buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.buffer);
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, draw);
    }

    /**
     * Updates the data of the buffer. Should only be used for dynamic buffer. Function assumes that the buffer
     * passed is a vertex buffer. No checks are performed to confirm that the buffer is a vertex buffer.
     */  
    void updateBuffer(const BufferData &buffer) noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.buffer);
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_DYNAMIC_DRAW);
    }

    void deleteBuffer(uint32_t &buffer) noexcept
    {
        glDeleteBuffers(1, &buffer);
    }
}