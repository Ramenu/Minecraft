#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float deltaTime;
extern float lastFrame;
extern bool firstMouse;
extern float lastX;
extern float lastY;

//Camera settings
extern float movementSpeed;
extern float mouseSensitivity;
extern float zoom;
//Euler angles
extern float yaw;
extern float pitch;
//Camera attributes
extern glm::vec3 cameraPos;
extern glm::vec3 cameraUp;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraRight;
extern glm::vec3 cameraDirection;
extern glm::vec3 worldUp;
extern glm::vec3 direction;
//Returns the view matrix calculated using euler angles and the lookAt matrix
extern glm::mat4 getViewMatrix();

//void updateCameraVectors();

#endif