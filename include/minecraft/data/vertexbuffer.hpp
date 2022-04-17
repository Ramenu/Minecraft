#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "glad/glad.h"

class VertexBuffer
{
    private:
        unsigned int vertexBuffer;
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

        inline unsigned int getBuffer() const noexcept {
            return vertexBuffer;
        }

};

#endif // VERTEXBUFFER_HPP
