#include "mylib/game.hpp"
#include <glm/glm.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    /*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    std::cout << cameraDirection.x << cameraDirection.y << cameraDirection.z << '\n';*/
    const unsigned int windowWidth {400}, windowHeight {400};
    Game minecraft(windowWidth, windowHeight);
    minecraft.startGame();
    return 0;
}
