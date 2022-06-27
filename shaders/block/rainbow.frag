#define PARABOLA(x, k) (pow(4.0*(x)*(1.0-(x)), (k)))
#define PI 3.14159265359
#define LINE_THICKNESS 0.2
#define PLOT(uv, pct) (smoothstep((pct)-LINE_THICKNESS, (pct), uv.y) - smoothstep((pct), (pct)+LINE_THICKNESS, uv.y))

float plot(vec2 uv, float pct, float thickness) {
    return smoothstep(pct-thickness, pct, uv.y) - smoothstep(pct, pct+thickness, uv.y);
}

float plotNotSmooth(vec2 uv, float pct, float thickness) {
    return step(pct-thickness, uv.y) - step(pct+thickness, uv.y);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;

    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 yellow = vec3(0.7, 0.9, 0.0);
    vec3 green = vec3(0.0, 1.0, 0.0);
    vec3 lightBlue = vec3(0.0, 0.7, 0.9);
    vec3 blue = vec3(0.0, 0.0, 1.0);
    
    float paraRed = PARABOLA(uv.x, 0.6)-0.04;
    float paraYellow = PARABOLA(uv.x, 0.8)-0.12;
    float paraGreen = PARABOLA(uv.x, 0.89)-0.18;
    float paraBlue = PARABOLA(uv.x, 0.96)-0.25;
    
    float lineRed = plot(uv, paraRed, 0.2);
    float lineYellow = plot(uv, paraYellow, 0.15);
    float lineGreen = plot(uv, paraGreen, 0.1);
    float lineBlue = plot(uv, paraBlue, 0.09);
    
    vec3 sky = (1.0 - (lineRed + lineBlue + lineGreen)) * lightBlue;
    vec3 redRainbow = vec3(lineRed) * red;
    vec3 yellowRainbow = vec3(lineYellow) * yellow;
    vec3 greenRainbow = vec3(lineGreen) * green;
    vec3 blueRainbow = vec3(lineBlue) * blue;
    
    vec3 color = sky + redRainbow + yellowRainbow + greenRainbow + blueRainbow;

    // Output to screen
    fragColor = vec4(color, 1.0);
}