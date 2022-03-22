#include "minecraft/shader/shader.hpp"
#include "minecraft/glerror/glerror.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

/** 
 * Loads the vertex and fragment shader and links them into 
 * the shader program, the arguments passed should 
 * be paths to where the shader code is located. 
 * If there are any errors during compilation or linking then 
 * it will print them to stderr. 
 */
Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) noexcept
{
    do 
    {
        // First check if any precompiled binaries are available for use
        if (!binaryAvailable(vertexShaderSource))
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
            const uint32_t vertexShader {glCreateShader(GL_VERTEX_SHADER)};
            glShaderSource(vertexShader, 1, &cstrVertexShaderCode, NULL);
            glCompileShader(vertexShader);
            checkShaderCompilationErrors(vertexShader, GL_VERTEX_SHADER, vertexShaderSource);

            // Compile fragment shader
            const std::string fragmentShaderCode {fragmentShaderStream.str()};
            const char *cstrFragmentShaderCode {fragmentShaderCode.c_str()};
            const uint32_t fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
            glShaderSource(fragmentShader, 1, &cstrFragmentShaderCode, NULL);
            glCompileShader(fragmentShader);
            checkShaderCompilationErrors(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);
            
            shaderProgram = glCreateProgram();

            // Attach the shaders together and link the program (and check for errors)
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            checkLinkageErrors();

            glDeleteShader(vertexShader); 
            glDeleteShader(fragmentShader);

            if (canCreateShaderBinary())
                createShaderBinary(vertexShaderSource);
        }
        else
        {
            
        }
    } while (true);
    
}

bool Shader::canCreateShaderBinary()
{
    int formats {};
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    return (formats < 1);
}

void Shader::createShaderBinary(const char *outputFile)
{
    int length {};
    glGetProgramiv(shaderProgram, GL_PROGRAM_BINARY_LENGTH, &length);

    // Get the binary code
    GLenum format {};
    std::vector<GLubyte> buffer (length);
    glGetProgramBinary(shaderProgram, length, NULL, &format, buffer.data());

    // Write binary to a file
    std::ofstream out {outputFile, std::ios::binary};
    out.write(reinterpret_cast<char*>(buffer.data(), length));
    out.close();

}

/**
 * Checks if shader compilation was successful. If not,
 * the program will print an error message to stderr before
 * terminating the program.
 */
void Shader::checkShaderCompilationErrors(const uint32_t& shader, int shaderType, const char *shaderPath) const noexcept
{
    int success {};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512] {};
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        GLError::error_message("Failed to compile shader \"" + std::string{shaderPath} + "\". " + std::string{infoLog});
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