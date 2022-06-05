#ifndef MC_SHADER_HPP
#define MC_SHADER_HPP

#include "glm/mat4x4.hpp"
#include "glad/glad.h"
#include <string>

class Shader
{
    private:
        GLuint shaderProgram;
        void checkShaderCompilationErrors(GLuint shader, const std::string &shaderPath) const noexcept;
        void checkLinkageErrors() const noexcept;
    public:
        Shader() = default;
        Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) noexcept;
        inline ~Shader() noexcept {
            glDeleteProgram(shaderProgram);
        }
        inline void useShader() const noexcept {glUseProgram(getShader());}
        inline void setMat4(const char *name, const glm::mat4 &matrix) const noexcept {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);
        }
        inline void setMat3(const char *name, const glm::mat3 &matrix) const noexcept {
            glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);
        }
        inline void setVec2(const char *name, const glm::vec2 &vec) const noexcept {
            glUniform2f(glGetUniformLocation(shaderProgram, name), vec.x, vec.y);
        }
        inline void setVec3(const char *name, const glm::vec3 &vec) const noexcept {
            glUniform3f(glGetUniformLocation(shaderProgram, name), vec.x, vec.y, vec.z);
        }
        inline void setInt(const char *name, int32_t value) const noexcept {
            glUniform1i(glGetUniformLocation(shaderProgram, name), value);
        }
        inline void setFloat(const char *name, float value) const noexcept {
            glUniform1f(glGetUniformLocation(shaderProgram, name), value);
        }
        inline GLuint getShader() const noexcept { return shaderProgram; }
};


#endif // MC_SHADER_HPP