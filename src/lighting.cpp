#include <glad/glad.h>
#include "mylib/lighting.hpp"

unsigned int Lighting::lightVao {};
//TODO: Make another class for positional light source later on
/* Constructor for lighting. Initializes the ambient, specular vector and the shader for the light as well. */
Lighting::Lighting(const float& ambient, const float& specular, const float& diffuse, const glm::vec3& directionVec, const glm::vec3& lightPos) :
lightShader {"shaders/light/lightvertexshader.vs", "shaders/light/lightfragmentshader.fs"},
ambientVec {glm::vec3(ambient)}, 
specularVec {glm::vec3(specular)}, 
diffuseVec {glm::vec3(diffuse)},
directionVec {glm::vec3(directionVec)},
lightPos {lightPos}
{
	
}

/* Class destructor for lighting. */
Lighting::~Lighting()
{

}

/* Deletes all the light vertex arrays, should be called only when the game process has exited. */
void Lighting::removeAllLights()
{
	glDeleteVertexArrays(1, &lightVao);
}

void Lighting::shaderProgramLightSource(const Shader& shader)
{
	shader.setVec3("light.ambient", ambientVec);
	shader.setVec3("light.diffuse", diffuseVec);
	shader.setVec3("light.specular", specularVec);
	shader.setVec3("light.direction", directionVec);
}

/* Initializes the vertex array for light. */
void Lighting::initLightVAO()
{
	glGenVertexArrays(1, &lightVao);
}

/* Binds the light vertex array. */
void Lighting::bindLightVAO()
{
	glBindVertexArray(lightVao);
}