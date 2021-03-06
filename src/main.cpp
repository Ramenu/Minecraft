#include "minecraft/game/game.hpp"
#include "minecraft/glerror/glerror.hpp"
#include "misc/terminal.h"
#include "GLFW/glfw3.h"
#include <cstring>
#include "minecraft/window/window.hpp"

int main(int argc, char **argv)
{
    static_assert(sizeof(std::size_t) >= 4, "Go buy a real computer");

    if (argc > 1)
        for (int i {}; i < argc; ++i)
            if (strcmp(argv[i], "-debug") == 0)
                Window::runningInDebugMode = true;

    #if defined(__MINGW32__) || defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
        if (enable_virtual_terminal_processing()) 
        {
            initGame("Minecraft");
            runGame();
        } 
        else
            GLError::error_message("Failed to enable virtual terminal processing");
    #else // ANSI color codes are automatically enabled on UNIX systems
        initGame("Minecraft");
        runGame();
    #endif
    glfwTerminate();
    return 0;
}
