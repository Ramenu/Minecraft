#include "minecraft/game/game.hpp"
#include <cstdint>
#include "minecraft/glerror/glerror.hpp"
extern "C"
{
    #include "misc/terminal.h"
}

int main()
{
    static_assert(sizeof(size_t) >= 4, "Go buy a real computer");
    #if defined(__MINGW32__) || defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
        if (enable_virtual_terminal_processing()) 
        {
            initGame("Minecraft");
            runGame();
        } 
        else
            GLError::error_message("Failed to enable virtual terminal processing");
    #else // ANSI color codes are automatically supported on UNIX systems
        initGame("Minecraft");
        runGame();
    #endif
    
    return 0;
}
