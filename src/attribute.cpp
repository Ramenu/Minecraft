#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include "mylib/attribute.hpp"


/* Sets the attribute location of the position and texture location. */
void setAttributes(const unsigned int& posAttrLocation, const unsigned int&textureAttrLocation)
{
    const unsigned int stride {posAttrLocation + textureAttrLocation};
    glVertexAttribPointer(0, posAttrLocation, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glVertexAttribPointer(1, textureAttrLocation, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(posAttrLocation * sizeof(float)));
}
    
/* Enables all of the attributes in the buffer (only up to the number passed). */
void enableVBOAttributes(unsigned int& buffer, const unsigned int& upTo)
{
    //static_assert(upTo < 4, "Only up to 3")
    for (unsigned int i {}; i < upTo; i++)
        glEnableVertexArrayAttrib(buffer, i);
}

/* Disables all of the attributes in the buffer (only up to the number passed). */
void disableVBOAttributes(unsigned int& buffer, const unsigned int& upTo)
{
    for (unsigned int i {}; i < upTo; i++)
        glDisableVertexArrayAttrib(buffer, i);
}

/* Enables the number of attributes in the vertex array passed. */
void enableVAOAttributes(const unsigned int& upTo)
{
    for (unsigned int i {}; i < upTo; i++)
        glEnableVertexAttribArray(i);
}

/* Disables the number of attributes in the vertex array passed. */
void disableVAOAttributes(const unsigned int& upTo)
{
    for (unsigned int i {}; i < upTo; i++)
        glDisableVertexAttribArray(i);
}