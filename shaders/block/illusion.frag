#define RATE 0.85
#define RATE_END 0.58

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    float timeRate = -iTime * RATE;

    float distCenter = 1.0 - step(mod(0.4 + timeRate, RATE_END), distance(uv, vec2(0.5)));
    float distBorder = step(mod(0.5 + timeRate, RATE_END), distance(uv, vec2(0.5)));
    float distOut = 1.0 - step(mod(0.7 + timeRate, RATE_END), distance(uv, vec2(0.5)));
    
    vec3 bg = vec3(1.0, 1.0, 1.0);
    vec3 centerCircle = bg * distCenter;
    vec3 borderCircle = bg * distBorder;
    vec3 outCircle = bg * distOut;
    
    vec3 col = centerCircle + borderCircle * outCircle;
    // Output to screen
    fragColor = vec4(col,1.0);
}
