#include "glad/glad.h"
#include "mylib/buffers/buffer.hpp"

namespace Buffer
{
    /* Loads the data into the vertex buffer passed. */
    void loadVertexBuffer(uint32_t& buffer, uint32_t size, const void* data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /* Loads the data into the element buffer passed. */
    void loadElementBuffer(uint32_t& buffer, uint32_t size, const void* data)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
}
