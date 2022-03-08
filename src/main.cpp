#include "minecraft/game.hpp"
#include <cstdint>
extern "C"
{
    #include <terminal.h>
}

int main()
{
    static_assert(sizeof(size_t) >= 4, "Go buy a real computer");
    if (enable_virtual_terminal_processing()) // ASCI colors don't work atm ;(
    {
        Game minecraft {"Minecraft"};
        minecraft.runGame();
    }
    return 0;
}
