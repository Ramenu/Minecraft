#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/glm.hpp"

enum class ShaderType {VERTEX, FRAGMENT};


class Shader
{
    public:
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader();
        void useShader() const;
        void setMat4(const char* name, const glm::mat4& matrix) const;
        void setMat3(const char* name, const glm::mat3& matrix) const;
        void setVec2(const char* name, const glm::vec2& vec) const;
        void setVec3(const char* name, const glm::vec3& vec) const;
        void setInt(const char* name, int value) const;
        void setFloat(const char* name, float value) const;
        inline unsigned int getShader() const {return shaderProgram;}
    private:
        unsigned int shaderProgram;
        const char* vertexShaderPath;
        const char* fragmentShaderPath;
        void checkShaderCompilationErrors(unsigned int& shader, ShaderType shaderType);
        void checkLinkageErrors();
};


#endif // SHADER_HPP