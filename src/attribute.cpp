#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include "mylib/attribute.hpp"

void setAttributesPos(unsigned int&& posAttributeLocation)
{
    glVertexAttribPointer(0, posAttributeLocation, GL_FLOAT, GL_FALSE, posAttributeLocation * sizeof(float), (void*)0);
}

void setAttributes(unsigned int&& posAttributeLocation, unsigned int&& textureAttributeLocation)
{
    const unsigned int stride {posAttributeLocation + textureAttributeLocation};
    glVertexAttribPointer(0, posAttributeLocation, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glVertexAttribPointer(1, textureAttributeLocation, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(posAttributeLocation * sizeof(float)));
}