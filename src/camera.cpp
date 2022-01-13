#include "mylib/camera.h"

//Initialize camera positions
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true; //Initialize firstMouse to true upon startup
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.

//Initialize the pitch, lastY and lastX variables to 0
float pitch {};
float lastY {};
float lastX {};

//Method that retrieves the current view matrix
glm::mat4 getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
}