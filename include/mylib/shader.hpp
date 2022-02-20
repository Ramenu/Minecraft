#ifndef SHADER_HPP
#define SHADER_HPP

#include "glm/glm.hpp"

enum class ShaderType {VERTEX, FRAGMENT};


class Shader
{
    public:
        explicit Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        Shader(const Shader& shader); 
        Shader& operator=(const Shader& shader);
        Shader& operator=(Shader&& shader);
        ~Shader();
        inline void useShader() const {glUseProgram(shaderProgram);};
        void setMat4(const char* name, const glm::mat4& matrix) const;
        void setMat3(const char* name, const glm::mat3& matrix) const;
        void setVec2(const char* name, const glm::vec2& vec) const;
        void setVec3(const char* name, const glm::vec3& vec) const;
        void setInt(const char* name, int32_t value) const;
        void setFloat(const char* name, float value) const;
        inline uint32_t getShader() const {return shaderProgram;}
    private:
        uint32_t shaderProgram;
        const char* vertexShaderPath;
        const char* fragmentShaderPath;
        void checkShaderCompilationErrors(uint32_t& shader, ShaderType shaderType);
        void checkLinkageErrors();
};


#endif // SHADER_HPP