#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "minecraft/shader.hpp"

class Lighting
{
    public:
        static void initLightVAO();
        static void bindLightVAO();
        Lighting(float ambient, float specular, float diffuse, const glm::vec3& direction, const glm::vec3& light);
        ~Lighting() = default;
		static void removeAllLights();
        void shaderProgramLightSource(const Shader& shader) const;
        Shader lightShader;
        glm::vec3 ambientVec;
        glm::vec3 specularVec;
        glm::vec3 diffuseVec;
        glm::vec3 directionVec;
        glm::vec3 lightPos;
    private:
        static uint32_t lightVao;

};

#endif // LIGHTING_HPP