
#define PI 3.14159265359

// Function from: https://iquilezles.org/articles/functions/
#define PARABOLA(x, k) (pow(4.0*(x)*(1.0-(x)), (k)))

/* Low 's' will result in sharp curves at the center, whereas a higher 's' will
   stabilize around the center. */
#define CURVE(n, s) (pow(min(cos(PI * (x) / 2.0), 1.0 - abs(x)), (s)))


#define LINE_THICKNESS 0.02
#define PLOT(uv, pct) (smoothstep((pct)-LINE_THICKNESS, (pct), uv.y) - smoothstep((pct), (pct)+LINE_THICKNESS, uv.y))

/* Performs a linear interpolation between 'x' and 'y' using 'a'
 * to weight between them. Use the built-in function instead of
 * this. This is only to provide a helpful reference of how it
 * works. */
#define MIX(x, y, a) ((x) * (1 - (a)) + (y) * (a))

/* Returns 0.0 when x is 1.0
 * Returns 1.0 when x is 0.0 */
#define NOT(x) (1.0 - (x))






