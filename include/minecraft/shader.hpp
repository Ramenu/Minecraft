#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/mat4x4.hpp"


class Shader
{
    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
        ~Shader() noexcept;
        void useShader() const noexcept;
        void setMat4(const char *name, const glm::mat4 &matrix) const noexcept;
        void setMat3(const char *name, const glm::mat3 &matrix) const noexcept;
        void setVec2(const char *name, const glm::vec2 &vec) const noexcept;
        void setVec3(const char *name, const glm::vec3 &vec) const noexcept;
        void setInt(const char *name, int32_t value) const noexcept;
        void setFloat(const char *name, float value) const noexcept;
        inline uint32_t getShader() const noexcept {return shaderProgram;}
    private:
        uint32_t shaderProgram;
        const char *vertexShaderPath {" "};
        const char *fragmentShaderPath {" "};
        void checkShaderCompilationErrors(const uint32_t &shader, int shaderType) const noexcept;
        void checkLinkageErrors() const noexcept;
};


#endif // SHADER_HPP