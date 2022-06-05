#ifndef MC_VERTEXBUFFER_HPP
#define MC_VERTEXBUFFER_HPP

#include "glad/glad.h"

class VertexBuffer
{
    private:
        GLuint vertexBuffer;
    public:

        inline VertexBuffer() noexcept {
            glGenBuffers(1, &vertexBuffer);
        }

        inline ~VertexBuffer() noexcept {
            glDeleteBuffers(1, &vertexBuffer);
        }

        inline void bind() const noexcept {
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        }

        inline GLuint getBuffer() const noexcept {
            return vertexBuffer;
        }

};

#endif // MC_VERTEXBUFFER_HPP
