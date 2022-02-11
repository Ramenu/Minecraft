#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include "mylib/attribute.hpp"


/* Sets the attribute locations, only requires a vector of the stride of each attribute. */
void setAttributes(std::vector<intptr_t>&& attributeIndices)
{
    intptr_t length {}, stride {};
    for (const auto&i: attributeIndices)
        length += i;

    for (size_t i {}; i < attributeIndices.size(); i++)
    {
        glVertexAttribPointer(i, attributeIndices.at(i), GL_FLOAT, GL_FALSE, length * sizeof(float), (void*)(stride * sizeof(float)));
        stride += attributeIndices.at(i);
    }
}
    
/* Enables all of the attributes in the buffer (only up to the number passed). */
void enableVBOAttributes(unsigned int& buffer,  const unsigned int upTo)
{
    //static_assert(upTo < 4, "Only up to 3")
    for (unsigned int i {}; i < upTo; i++)
        glEnableVertexArrayAttrib(buffer, i);
}

/* Disables all of the attributes in the buffer (only up to the number passed). */
void disableVBOAttributes(unsigned int& buffer, const unsigned int upTo)
{
    for (unsigned int i {}; i < upTo; i++)
        glDisableVertexArrayAttrib(buffer, i);
}

/* Enables the number of attributes in the vertex array passed. */
void enableVAOAttributes(std::vector<unsigned int>&& indices)
{
    for (const auto&i: indices)
        glEnableVertexAttribArray(i);
}        

/* Disables the number of attributes in the vertex array passed. */
void disableVAOAttributes(std::vector<unsigned int>&& indices)
{
    for (const auto&i: indices)
        glDisableVertexAttribArray(i);
}