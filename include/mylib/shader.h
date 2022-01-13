#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mylib/vertices.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

class Shader{
    public:
        void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        void useShader();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void drawBlock();
        void translateAndDrawBlock(glm::vec3 transformedVertices);
        void passTexturesToShaders(unsigned int texture1, unsigned int texture2, unsigned int texture3);
        void loadVertexData(std::vector<glm::vec3> positionData);
        unsigned int shaderProgram;
    private:
        unsigned int shaderTexture1;
        unsigned int shaderTexture2;
        unsigned int shaderTexture3;
        void check_Shader_Compilation_Errors(unsigned int shader, const char* type);
};


#endif