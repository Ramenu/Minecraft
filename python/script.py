c = [0.0, 0.0, 0.0]
p = [2.0, 4.0, 3.0]

# Parametric ray intuition
# Takes 't' as input and returns an array of a 3D vector (x, y, z)
def rayIntuition(t):
    x = (1 - t) * c[0] + t * p[0]
    y = (1 - t) * c[1] + t * p[1]
    z = (1 - t) * c[2] + t * p[2]
    return [x, y, z]

ray = rayIntuition(2.0)
print(ray)