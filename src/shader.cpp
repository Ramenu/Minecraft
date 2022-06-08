#include "minecraft/shader/shader.hpp"
#include "minecraft/glerror/glerror.hpp"
#include <fstream>
#include <sstream>

/** 
 * Loads the vertex and fragment shader and links them into 
 * the shader program, the arguments passed should 
 * be paths to where the shader code is located. 
 * If there are any errors during compilation or linking then 
 * it will print them to stderr. 
 */
Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) noexcept
{
    std::stringstream vertexShaderStream, fragmentShaderStream;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.open(vertexShaderSource);
    fragmentShaderFile.open(fragmentShaderSource);

    // Read file contents into the string streams
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();
    
    // Compile vertex shader
    const std::string vertexShaderCode {vertexShaderStream.str()};
    const char *cstrVertexShaderCode {vertexShaderCode.c_str()};
    const GLuint vertexShader {glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &cstrVertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(vertexShader, vertexShaderSource);

    // Compile fragment shader
    const std::string fragmentShaderCode {fragmentShaderStream.str()};
    const char *cstrFragmentShaderCode {fragmentShaderCode.c_str()};
    const GLuint fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &cstrFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilationErrors(fragmentShader, fragmentShaderSource);
    
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
void Shader::checkShaderCompilationErrors(GLuint shader, const std::string &shaderPath) const noexcept
{
    int success {};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        static constexpr std::size_t INFO_LOG_SIZE {512};
        char infoLog[INFO_LOG_SIZE] {};
        glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, static_cast<char*>(infoLog));
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
        static constexpr std::size_t INFO_LOG_SIZE {512};
        char infoLog[INFO_LOG_SIZE] {};
        glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, NULL, static_cast<char*>(infoLog));
        GLError::error_message("Failed to link shader program:\n" + std::string{infoLog});
    }
}