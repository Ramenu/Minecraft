#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "mylib/buffers/buffer.hpp"

/* Loads the data into the vertex buffer passed. */
void loadVertexBuffer(unsigned int& buffer, unsigned int size, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/* Loads the data into the element buffer passed. */
void loadElementBuffer(unsigned int& buffer, unsigned int size, const void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
