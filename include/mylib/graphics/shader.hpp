#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

enum class ShaderType {VERTEX, FRAGMENT};

class Shader
{
    public:
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader();
        void useShader();
        void setMat4(const char* name, const glm::mat4& matrix) const;
        void setMat3(const char* name, const glm::mat3& matrix) const;
        void setVec2(const char* name, const glm::vec2& vec) const;
        void setVec3(const char* name, const glm::vec3& vec) const;
        void setInt(const char* name, const int& value) const;
        void setFloat(const char* name, const float& value) const;
        unsigned int shaderProgram;
    private:
        void checkShaderCompilationErrors(unsigned int &shader, ShaderType shaderType);
        void checkLinkageErrors();
};


#endif