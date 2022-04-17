#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glad/glad.h"

class VertexArray
{
    private:
        unsigned int vertexArray;
    public:
        inline VertexArray() noexcept {
            glGenVertexArrays(1, &vertexArray);
        }

        inline ~VertexArray() noexcept {
            glDeleteVertexArrays(1, &vertexArray);
        }

        inline void bind() const noexcept {
            glBindVertexArray(vertexArray);
        }

};

#endif // VERTEXARRAY_HPP
