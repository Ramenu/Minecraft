
#define NOT(x) (1.0 - (x))
float rect(in vec2 uv, in vec2 edge1, in vec2 edge2)
{   
    float xOffset = step(edge1.x, uv.x) * NOT(step(edge1.x + edge2.x, uv.x));
    float yOffset = step(edge1.y, uv.y) * NOT(step(edge1.y + edge2.y, uv.y));
    
    return xOffset * yOffset;
}

float smoothrect(in vec2 uv, in vec2 edge1, in vec2 edge2)
{
    float xOffset = smoothstep(abs(edge2.x - edge1.x), edge1.x, uv.x)
                    * NOT(smoothstep(edge1.x, edge1.x + edge2.x, uv.x));
    float yOffset = smoothstep(abs(edge2.y - edge1.y), edge1.y, uv.y) 
                    * NOT(smoothstep(edge1.y, edge1.y + edge2.y, uv.y));
    return xOffset * yOffset;
}

float rectOutline(in vec2 uv, in vec2 edge1, in vec2 edge2)
{
    #define DISTANCE 0.002
    float xOffset = step(edge1.x, uv.x) * NOT(step(edge1.x + edge2.x, uv.x));
    
    float xBorder =  min(1.0, step(abs(edge1.x - uv.x), DISTANCE) + 
                              step(abs(edge1.x + edge2.x - uv.x), DISTANCE)) *
                     NOT(step(edge2.y + edge1.y, uv.y)) *
                     step(edge1.y, uv.y);
   
    float yOffset = step(abs(edge1.y - uv.y), DISTANCE) + 
                    step(abs(edge2.y + edge1.y - uv.y), DISTANCE);
    
    return xOffset * (yOffset + xBorder);
    #undef DISTANCE
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    vec2 area = vec2(0.1, 0.4);
    vec3 col = vec3(1.0)*rect(uv, area);
    
    // Output to screen
    fragColor = vec4(col,1.0);
}
