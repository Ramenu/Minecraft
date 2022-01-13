#ifndef VERTICES_H
#define VERTICES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "mylib/shader.h"

extern const float vertices[180];
extern unsigned int indices[6];
extern std::vector<glm::vec3> grassBlockPositions;

#endif