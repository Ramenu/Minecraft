#include "Glad/glad.h"
#include "minecraft/attribute.hpp"


/**
 * Sets the attribute locations, only requires a 
 * vector of the stride of each attribute. 
 */
void setAttributes(const std::vector<intptr_t> &attributeIndices)
{
    intptr_t length {}, stride {};
    for (const auto&i: attributeIndices)
        length += i;

    for (size_t i {}; i < attributeIndices.size(); i++)
    {
        glVertexAttribPointer(i, 
                              attributeIndices.at(i), 
                              GL_FLOAT, 
                              GL_FALSE, 
                              length * sizeof(float), 
                              reinterpret_cast<void*>(stride * sizeof(float)));
        stride += attributeIndices.at(i);
    }
}
    
/** 
 * Enables all of the attributes in the buffer 
 * (only up to the number passed).  
 */
void enableVBOAttributes(const uint32_t &buffer, uint32_t upTo)
{
    for (uint32_t i {}; i < upTo; i++)
        glEnableVertexArrayAttrib(buffer, i);
}

/** 
 * Disables all of the attributes in the buffer (only up to the number passed).  
 */
void disableVBOAttributes(const uint32_t &buffer, uint32_t upTo)
{
    for (uint32_t i {}; i < upTo; i++)
        glDisableVertexArrayAttrib(buffer, i);
}

/**
 * Enables the attributes that are inside of the indices.
 */
void enableVAOAttributes(const std::vector<uint32_t> &indices)
{
    for (const auto&i: indices)
        glEnableVertexAttribArray(i);
}        

/**
 * Disables the attributes that are inside of the indices.
 */
void disableVAOAttributes(const std::vector<uint32_t> &indices)
{
    for (const auto&i: indices)
        glDisableVertexAttribArray(i);
}