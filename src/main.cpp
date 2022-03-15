#include "minecraft/game.hpp"
#include <cstdint>
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
            Game minecraft {"Minecraft"};
            minecraft.runGame();
        } 
        else
            return 1;
    #else
        Game minecraft {"Minecraft"};
        minecraft.runGame();
    #endif
    
    return 0;
}
