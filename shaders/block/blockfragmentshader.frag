#version 460 core

#define FOG_DENSITY (0.007)
#define FOG_GRADIENT (1.5)

struct Material 
{
    sampler2D diffuse;
    vec3 specular;
    float shine;
    float ambient;
};

struct Light
{
    vec3 position; // <-- Position is not necessary when using directional lights
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 fragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float blockAmbient;

uniform sampler2D allTextures;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
    //fragColor = vec4(lightColor * objectColor, 1.0);
    //fragColor = texture(allTextures, TexCoord) * (ambient * objectColor, 1.0);

    /* Ambient */
    const vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord)) * blockAmbient;
   
    /* Diffuse */
    const vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos); // Calculate difference between vectors
    const vec3 lightDir = normalize(-light.direction);

    // If the angle between both vectors is greater than 90 degrees the result of the dot product will be negative, which will result in
    // a negative diffuse component
    const float diff = max(dot(norm, lightDir), 0.0); // Calculate diffuse impact of the light 
    const vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    const vec3 result = (ambient + diffuse);

    fragColor = vec4(result, 1.0);
}