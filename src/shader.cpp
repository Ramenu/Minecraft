#include "minecraft/shader.hpp"
#include "minecraft/glerror.hpp"
#include <fstream>
#include <sstream>

/** 
 * Loads the vertex and fragment shader and links them into 
 * the shader program, the arguments passed should 
 * be paths to where the shader code is located. 
 * If there are any errors during compilation or linking then 
 * it will print them to stderr. 
 */
Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) :
vertexShaderPath {vertexShaderSource},
fragmentShaderPath {fragmentShaderSource}
{

    std::stringstream vertexShaderStream, fragmentShaderStream;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    try
    {
        // Set exceptions to be thrown
        vertexShaderFile.exceptions(std::ios::failbit | std::ifstream::failbit);
        fragmentShaderFile.exceptions(std::ios::failbit | std::ifstream::failbit);

        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        // Read file contents into the string streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();
    }
    catch (const std::ifstream::failure &e)
    {
        GLError::error_message(std::string{"Shader compilation failed:\n" + std::string{e.what()}});
    }
    
    // Compile vertex shader
    const std::string vertexShaderCode {vertexShaderStream.str()};
    const char* cstrVertexShaderCode {vertexShaderCode.c_str()};
    const uint32_t vertexShader {glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &cstrVertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(vertexShader, GL_VERTEX_SHADER);

    // Compile fragment shader
    const std::string fragmentShaderCode {fragmentShaderStream.str()};
    const char* cstrFragmentShaderCode {fragmentShaderCode.c_str()};
    const uint32_t fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &cstrFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilationErrors(fragmentShader, GL_FRAGMENT_SHADER);
    
    shaderProgram = glCreateProgram();

    // Attach the shaders together and link the program (and check for errors)
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkLinkageErrors();

    glDeleteShader(vertexShader); 
    glDeleteShader(fragmentShader);
}


/**
 * Checks if shader compilation was successful. If not,
 * the program will print an error message to stderr before
 * terminating the program.
 */
void Shader::checkShaderCompilationErrors(const uint32_t& shader, int shaderType) const noexcept
{
    int success {};
    std::string shaderPath {(shaderType == GL_VERTEX_SHADER) ? vertexShaderPath : fragmentShaderPath};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512] {};
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        GLError::error_message("Failed to compile shader \"" + shaderPath + "\". " + std::string{infoLog});
    }
}

/* Checks if the program linking was unsuccessful. */
void Shader::checkLinkageErrors() const noexcept
{
    int success {};
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512] {};
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        GLError::error_message("Failed to link shader program:\n" + std::string{infoLog});
    }
}