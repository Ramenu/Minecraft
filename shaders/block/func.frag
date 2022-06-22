
#define PI 3.14159265359

/* The lower the curve, the more it flattens out at the edges
   (it is recommended that the curve be 2.0 for an actual parabola shape). */
#define PARABOLA(x, curve) (1.0 - pow(abs(sin(PI * (x) / 2.0)), (curve)))

/* Low 's' will result in sharp curves at the center, whereas a higher 's' will
   stabilize around the center. */
#define CURVE(n, s) (pow(min(cos(PI * (x) / 2.0), 1.0 - abs(x)), (s)))



