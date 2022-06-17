import numpy as np
import random
from math import pi, cos, sin

def lerp(a : float, b : float, t : float) -> float:
    return a + t * (b - a);

def randf() -> float:
    return random.uniform(0.0, pi * 2.0)

def fade(t : float) -> float:
    return ((6.0*t - 15.0)*t + 10.0)*t*t*t;

def getRandom2DUnitVector() -> list:
    angle = randf()
    return [cos(angle), sin(angle)]

def generate2DGradients() -> list:
    return [
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector(),
        getRandom2DUnitVector()
    ]

def clamp(minN, maxN, n):
    if n <= minN:
        return minN
    if n >= maxN:
        return maxN
    return n


def perlin(p1 : float, p2 : float, gradients : list) -> float:

    point = [p1*0.01, p2*0.01]
    d1 = np.dot(point, gradients[0])
    d2 = np.dot(point, gradients[1])
    d3 = np.dot(point, gradients[2])
    d4 = np.dot(point, gradients[3])

    t1 = fade(p1)
    t2 = fade(p2)

    li1 = lerp(d1, d2, t1)
    li2 = lerp(d3, d4, t1)
    return lerp(li1, li2, t2)

def getColor(p1, p2, gradients) -> int:
    p = perlin(p1, p2, gradients)

    # Transform range to [0.0, 1.0] assuming range of perlin is [-1.0, 1.0]
    p += 1.0
    p /= 2.0
    p = clamp(0.0, 1.0, p)
    return round(p*15.0)

def generateChunk(width : int, height : int):
    DO_PERLIN = 1
    if DO_PERLIN:
        print("Doing perlin")
    else:
        print("Doing random")
    chunk = [[0] * width for i in range(height)]
    longest = width
    if height > longest:
        longest = height
    gradients = generate2DGradients()
    for x in range(width):
        for y in range(height):
            if DO_PERLIN:
                chunk[x][y] = getColor(x, y, gradients, longest)
            else:
                chunk[x][y] = random.randint(0, 1)


    # Start printing
    for x in range(width):
        for y in range(height):
            if chunk[x][y] == 1:
                print("/",end="")
            elif chunk[x][y] == 0:
                print("", end="")
        print("")

p1 = 2.0
p2 = 2.0
gradients = generate2DGradients()
print(getColor(p1, p2, gradients))


