import numpy
import math
import time
from datetime import datetime

def getTriangleArea(p1, p2, p3):
    vec1 = numpy.subtract(p2, p1)
    vec2 = numpy.subtract(p3, p1)
    orthoVector = numpy.cross(vec1, vec2)
    u = math.sqrt(pow(orthoVector[0], 2) + pow(orthoVector[1], 2) + pow(orthoVector[2], 2))
    area = u / 2
    return area

def getBarycentricCoords(a, b, c, p):
    v0 = numpy.subtract(b, a) 
    v1 = numpy.subtract(c, a) 
    v2 = numpy.subtract(p, a) 
    invden = 1.0 / (v0[0] * v1[1] - v1[0] * v0[1]) # Calculate area
    v = (v2[0] * v1[1] - v1[0] * v2[1]) * invden 
    w = (v0[0] * v2[1] - v2[0] * v0[1]) * invden 
    u = 1.0 - v - w 
    return [v, w, u]

a = [5, 2, 5]
b = [-3, 3, 5]
c = [4, -4, 4]
i = [0.9, 1.9, 4.9]

start = time.time()
bary = getBarycentricCoords(a, b, c, i)
end = time.time()
print("Time elapsed:", end - start)
