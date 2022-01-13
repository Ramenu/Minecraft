#include "mylib/shader.h"

void Shader::loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    //Retrieve vertex/fragment shader code from the filepath
    std::string vertexShaderCodeString;
    std::string fragmentShaderCodeString;
    std::ifstream vertexShaderFile(vertexShaderSource);
    std::ifstream fragmentShaderFile(fragmentShaderSource);

    //Ensure the shader files can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try 
    {

        //Read file's buffer contents into string stream
        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        //Close files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //Convert the streams strings so then we convert them into constant characters
        vertexShaderCodeString = vertexShaderStream.str();
        fragmentShaderCodeString = fragmentShaderStream.str();
    }
    //Catch ifstream exceptions
    catch (std::ifstream::failure& e)
    {
        std::cout << "\nFailed to read shader file!\n";
        printf("ERROR: %s\n", e.what());
    }

    //Convert it to constant characters
    const char* vertexShaderCode {vertexShaderCodeString.c_str()};
    const char* fragmentShaderCode {fragmentShaderCodeString.c_str()};

    //Create the vertex shader and tell the compiler its source (and check for the compiler errors)
    unsigned int vertexShader {glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    check_Shader_Compilation_Errors(vertexShader, "VERTEX SHADER");

    //Same thing with the fragment shader
    unsigned int fragmentShader {glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    check_Shader_Compilation_Errors(fragmentShader, "FRAGMENT SHADER");

    //Create the shader program
    shaderProgram = glCreateProgram();

    //Attach the shaders together and link the program (and check for the compiler errors)
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_Shader_Compilation_Errors(shaderProgram, "PROGRAM"); //Checks if program linking was successful

    glDeleteShader(vertexShader); //Delete shaders afterwards because the program is already linked, wastes space!
    glDeleteShader(fragmentShader);
}

//Method that allows us to draw blocks
void Shader::drawBlock()
{
    //If texture2 is 0 then we automatically know that there is only one assigned texture to the block
        //If it isn't, bind the appropriate textures and then draw the block
    glBindTexture(GL_TEXTURE_2D, shaderTexture1);
    glDrawArrays(GL_TRIANGLES, 30, 36);
    glBindTexture(GL_TEXTURE_2D, shaderTexture2);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glBindTexture(GL_TEXTURE_2D, shaderTexture3);
    glDrawArrays(GL_TRIANGLES, 24, 30);
}

//Public method that allows us to use our shader program
void Shader::useShader()
{
    glUseProgram(shaderProgram);
}

void Shader::passTexturesToShaders(unsigned int texture1, unsigned int texture2, unsigned int texture3)
{
    shaderTexture1 = texture1;
    shaderTexture2 = texture2;
    shaderTexture3 = texture3;
}


//Method that checks if there were any compilation errors for the shaders
//First parameter specifies the shader, and the second argument specifies the type e.g. "VERTEX SHADER", "FRAGMENT SHADER", "PROGRAM"
void Shader::check_Shader_Compilation_Errors(unsigned int shader, const char* type)
{
    int success; //Define integer to indicate success
    char infoLog[1024]; //An storage array for the any error messages

    //If the type is not a program, then do not check for the link status but instead the shader compilation
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //Check if compilation was successful

        //If it wasn't, an infolog will be printed out along with the type of the shader
        if (!success);
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("\nSHADER COMPILATION OF TYPE %s: \n%s\n", type, infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success); //Check if program linking was successful

        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("\nPROGRAM LINKING ERROR:\n%s", infoLog);
        }
    }
}

void Shader::loadVertexData(std::vector<glm::vec3> positionData)
{
    for (unsigned int i = 0; i < positionData.size(); i++)
    {
        translateAndDrawBlock(positionData[i]);
    }
}


void Shader::translateAndDrawBlock(glm::vec3 transformedVertices)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transformedVertices);
    drawBlock();
    setMat4("model", model);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y); 
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z); 
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w); 
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}