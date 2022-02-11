#ifndef GLMATH_HPP
#define GLMATH_HPP

#include <cmath>
#include "glm/glm.hpp"
#include "mylib/math/average.hpp"
#include "mylib/math/line.hpp"

extern glm::vec3 getBarycentricCoords(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& p);

#endif // GLMATH_HPP
