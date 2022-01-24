#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include <glm/glm.hpp>
#include "mylib/graphics/shader.hpp"

class Lighting
{
    public:
        static void initLightVAO();
        static void bindLightVAO();
        Lighting(const float& ambient, const float& specular, const float& diffuse, const glm::vec3& directionVec, const glm::vec3& lightPos);
        ~Lighting();
		void removeAllLights();
        void shaderProgramLightSource(const Shader& shader);
        Shader lightShader;
        glm::vec3 ambientVec;
        glm::vec3 specularVec;
        glm::vec3 diffuseVec;
        glm::vec3 directionVec;
        glm::vec3 lightPos;
    private:
        static unsigned int lightVao;

};


#endif
