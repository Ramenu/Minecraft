#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "mylib/shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/* Loads the vertex and fragment shader and links them into the shader program, the arguments passed should be paths to where the
   shader code is located, if there are any errors during compilation then it will print them out as well. */
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    vertexShaderPath = vertexShaderSource;
    fragmentShaderPath = fragmentShaderSource;

    // Open the files
    std::ifstream vertexShaderFile {vertexShaderSource};
    std::ifstream fragmentShaderFile {fragmentShaderSource};
    std::stringstream vertexShaderStream, fragmentShaderStream;

    // Ensure the ifstreams can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try 
    {
        // Read file's contents into string stream
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "ERROR: Failed to read shader file: " << e.what() << '\n';
    }

    std::string vertexShaderCode {vertexShaderStream.str()};
    const char* cstrVertexShaderCode {vertexShaderCode.c_str()};
    unsigned int vertexShader {glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &cstrVertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(vertexShader, ShaderType::VERTEX);

    std::string fragmentShaderCode {fragmentShaderStream.str()};
    const char* cstrFragmentShaderCode {fragmentShaderCode.c_str()};
    unsigned int fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &cstrFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilationErrors(fragmentShader, ShaderType::FRAGMENT);
    
    shaderProgram = glCreateProgram();

    // Attach the shaders together and link the program (and check for errors)
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkLinkageErrors();

    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
}

/* Checks if the shader passed has an error in its code, if so it will print an error log containing the errors found within it. */
void Shader::checkShaderCompilationErrors(unsigned int &shader, ShaderType shaderType)
{
    int success;
    char infoLog[512];
    const char* shaderPath {(shaderType == ShaderType::VERTEX) ? vertexShaderPath : fragmentShaderPath};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "\nERROR: failed to compile shader \"" << shaderPath << "\":\n" << infoLog;
    }
}

/* Checks if the program linking was unsuccessful. */
void Shader::checkLinkageErrors()
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "\nERROR: Failed to link shader program:\n" << infoLog;
    }
}

/* Destructor for Shader. */
Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

/* Uses this shader program. */
void Shader::useShader() const
{
    glUseProgram(shaderProgram);
}

void Shader::setInt(const char* name, const int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setFloat(const char* name, const float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::setVec2(const char* name, const glm::vec2& vec) const
{
    glUniform2f(glGetUniformLocation(shaderProgram, "subTextureCoords"), vec.x, vec.y);
}

void Shader::setVec3(const char* name, const glm::vec3& vec) const
{
    glUniform3f(glGetUniformLocation(shaderProgram, name), vec.x, vec.y, vec.z);
}

void Shader::setMat3(const char* name, const glm::mat3& matrix) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);
}

/* Passes the 4x4 matrix to the shader to GLSL. */
void Shader::setMat4(const char* name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &matrix[0][0]);
}