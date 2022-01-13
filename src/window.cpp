#include "mylib/window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Method that loads the window and automatically does the tedious work, the window as 1st parameter and the name of it as the second
GLFWwindow* Window::loadWindow(GLFWwindow* window, const char* title)
{
    //Specify version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //If an apple machine (in this case, it isn't)
    #endif
    window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL); //Create the window
    //Occurs if window or OpenGL context creation fails (prints an error message and the title of the window)
    if (window == NULL)
    {
        glfwTerminate();
        printf("Failed to contextualize %s window\n", title);
        exit(-1);
    } 
    return window; //Return the window
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void on_Mouse_Button(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "\nyes\n";
    }
}

//Method that allows user input
void Window::key_callback(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE); //Exits the window upon pressing ESC
    }

    //Converts screen coordinates to normalized device coordinates upon pressing C and prints the coordinates
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        double normalizedX = -1.0 + 2.0 * xPos / screenWidth;
        double normalizedY = 1.0 - 2.0 * yPos / screenHeight;

        std::cout << "Cursor position at (" << normalizedX << ", " << normalizedY << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    float cameraSpeed = 2.5 * deltaTime;

    //These cover movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if (wireFrameMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireFrameMode = false;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireFrameMode = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

//Mouse callback method (retrieves mouse input) which gets passed into GLFW
//Window as the first parameter, and the X and Y cursor position of the screen gets passed in as the next arguments
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Boolean to check if this is the first time we receive mouse input
    if (firstMouse)
    {
        //If so, update the initial positions to the new xpos and ypos values
        lastX = xpos;
        lastY = ypos;
        firstMouse = false; //Initalize the bool to false
    }

    //Initialize the offset movement (aka how much the mouse moved) since the last frame
    float xOffSet = xpos - lastX;
    float yOffSet = lastY - ypos; //Reversed since y-coordinates range from bottom to top

    //Update the lastX and lastY values
    lastX = xpos;
    lastY = ypos;

    //Adjust our sensitivity (can be adjusted)
    const float sensitivity = 0.3f;
    xOffSet *= sensitivity;
    yOffSet *= sensitivity;

    //Add the offset values to the yaw and pitch values
    yaw += xOffSet;
    pitch += yOffSet;

    //Add constraints so that the pitch does not become too big or low (so it doesnt make weird camera movements)
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    //Then just do some trigs which GLM automatically does for us
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

}