#include "minecraft/game.hpp"
#include <cstdint>
#include "minecraft/glerror.hpp"
extern "C"
{
    #include <terminal.h>
}

int main()
{
    static_assert(sizeof(size_t) >= 4, "Go buy a real computer");
    #ifdef _WIN32
        if (enable_virtual_terminal_processing()) // ASCI colors don't work atm ;(
        {
            initGame("Minecraft");
            runGame();
        } 
        else
            GLError::error_message("Failed to enable virtual terminal processing");
    #else // ASCI color codes are automatically supported on UNIX systems
        initGame("Minecraft");
        runGame();
    #endif
    
    return 0;
}
