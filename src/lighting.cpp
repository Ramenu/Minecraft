#include "glad/glad.h"
#include "minecraft/lighting/lighting.hpp"

uint32_t Lighting::lightVao {};
//TODO: Make another class for positional light source later on

/**
 * Initializes the light source.
 */
Lighting::Lighting(const LightComponents &componentsOfLight, const glm::vec3 &direction, const glm::vec3 &lightPosition) noexcept :
components {componentsOfLight},
directionVec {direction},
position {lightPosition}
{
	
}


/** Deletes the light vertex array. This should be called only in 
 *  the renderer object's destructor.
 */
void Lighting::removeAllLights() noexcept
{
	glDeleteVertexArrays(1, &lightVao);
}

/**
 * Updates the shader's vectors to the light's vectors.
 */
void Lighting::shaderProgramLightSource(const Shader &shader) const noexcept
{
	shader.setVec3("light.ambient", components.ambient);
	shader.setVec3("light.diffuse", components.diffuse);
	shader.setVec3("light.specular", components.specular);
	shader.setVec3("light.direction", directionVec);
}


void Lighting::initLightVAO() noexcept
{
	glGenVertexArrays(1, &lightVao);
}

void Lighting::bindLightVAO() noexcept
{
	glBindVertexArray(lightVao);
}