#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include "mylib/camera.hpp"

extern GLFWwindow* loadWindow(GLFWwindow* window, const char* title);
extern void initWindow(const char* windowName, double windowWidth, double windowHeight);
inline unsigned int screenWidth;
inline unsigned int screenHeight;
extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
extern void processKeyboardInput(float deltaTime, Camera* camera);
extern void renderWireframes();
extern void destroyWindow();
inline bool wireframeMode;
extern GLFWwindow* glfwWindow;

#endif // WINDOW_HPP