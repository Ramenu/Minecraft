#include "glad/glad.h"
#include "minecraft/buffers/buffer.hpp"

namespace Buffer
{
    /* Loads the data into the buffer passed. Should be called during the initialization of a buffer object only. */
    void createBuffer(BufferData& buffer)
    {
        int bufferType = (buffer.isVertexBuffer) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
        int draw = (buffer.isStatic) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
        glGenBuffers(1, &buffer.buffer);
        glBindBuffer(bufferType, buffer.buffer);
        glBufferData(bufferType, buffer.size, buffer.data, draw);
    }

    /* Updates the data of the buffer. Should only be used for dynamic buffer. Function assumes that the buffer
       passed is a vertex buffer. */
    void updateBuffer(const BufferData& buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.buffer);
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, GL_DYNAMIC_DRAW);
    }
}