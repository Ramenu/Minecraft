#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "minecraft/shader.hpp"

struct LightComponents
{
    glm::vec3 ambient;
    glm::vec3 specular;
    glm::vec3 diffuse;
};

class Lighting
{
    private:
        LightComponents components;
        glm::vec3 directionVec;
        static uint32_t lightVao;
    public:
        static void initLightVAO() noexcept;
        static void bindLightVAO() noexcept;
        Lighting(const LightComponents &componentsOfLight, const glm::vec3 &direction, const glm::vec3 &position) noexcept;
        ~Lighting() = default;
		static void removeAllLights() noexcept;
        void shaderProgramLightSource(const Shader &shader) const noexcept;
        Shader lightShader {"shaders/light/lightvertexshader.vert", "shaders/light/lightfragmentshader.frag"};
        glm::vec3 position;

};

#endif // LIGHTING_HPP
