#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

class Shader
{
    public:
        void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void useShader();
        void deleteShaderProgram();
        void setMat4(const char* name, const glm::mat4 &matrix) const;
        enum class ShaderType {VERTEX, FRAGMENT};
    private:
        void checkShaderCompilationErrors(unsigned int &shader, ShaderType shaderType);
        void checkLinkageErrors();
        unsigned int shaderProgram;
};


#endif