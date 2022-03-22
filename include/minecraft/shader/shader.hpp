#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/mat4x4.hpp"
#include "glad/glad.h"


class Shader
{
    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource) noexcept;
        ~Shader() noexcept {glDeleteProgram(shaderProgram);}
        inline void useShader() const noexcept {glUseProgram(shaderProgram);}
        inline void setMat4(const char *name, const glm::mat4 &matrix) const {glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);}
        inline void setMat3(const char *name, const glm::mat3 &matrix) const {glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);}
        inline void setVec2(const char *name, const glm::vec2 &vec)  const {glUniform2f(glGetUniformLocation(shaderProgram, name), vec.x, vec.y);}
        inline void setVec3(const char *name, const glm::vec3 &vec) const {glUniform3f(glGetUniformLocation(shaderProgram, name), vec.x, vec.y, vec.z);}
        inline void setInt(const char *name, int32_t value) const {glUniform1i(glGetUniformLocation(shaderProgram, name), value);}
        inline void setFloat(const char *name, float value) const {glUniform1f(glGetUniformLocation(shaderProgram, name), value);}
        inline uint32_t getShader() const noexcept {return shaderProgram;}
    private:
        bool binaryAvailable(const char *fileName);
        bool canCreateShaderBinary();
        void createShaderBinary(const char *outputFile);
        void loadShaderBinary(const char *binaryFile);
        uint32_t shaderProgram;
        void checkShaderCompilationErrors(const uint32_t &shader, int shaderType, const char *shaderPath) const noexcept;
        void checkLinkageErrors() const noexcept;
};


#endif // SHADER_HPP