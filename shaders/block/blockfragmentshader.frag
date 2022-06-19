#version 460 core

#define FOG_DENSITY 0.007
#define FOG_GRADIENT 1.5
#define LOWEST_AMBIENT -0.2
#define DIFFUSE_VECTOR vec3(0.7, 0.7, 0.7)
#define AMBIENT_VECTOR vec3(0.25, 0.25, 0.25)

struct Material 
{
    sampler2D diffuse;
    float ambient;
};

out vec4 fragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float blockAmbient;
in float blockOpacity;

uniform sampler2D allTextures;
uniform Material material;


void main()
{
    const vec3 direction = normalize(vec3(1.0, 1.0, 0.0));

    const vec3 texDiffuse = vec3(texture(material.diffuse, TexCoord));

    /* Ambient */
    const vec3 ambient = AMBIENT_VECTOR * texDiffuse * blockAmbient;
   
    /* Diffuse */
    const float diff = max(dot(Normal, direction), LOWEST_AMBIENT); // Calculate diffuse impact of the light 
    const vec3 diffuse = DIFFUSE_VECTOR * diff * texDiffuse;

    const vec3 result = (ambient + diffuse);

    fragColor = vec4(result, blockOpacity);
}