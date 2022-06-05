#ifndef MC_VERTEXARRAY_HPP
#define MC_VERTEXARRAY_HPP

#include "glad/glad.h"

class VertexArray
{
    private:
        GLuint vertexArray;
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

#endif // MC_VERTEXARRAY_HPP
