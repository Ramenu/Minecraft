#include "minecraft/game.hpp"

int main()
{
    static_assert(sizeof(size_t) >= 4, "Integer must be at least 4 bytes to run program.");
    constexpr uint16_t windowWidth {512}, windowHeight {512};
    Game minecraft {windowWidth, windowHeight};
    minecraft.runGame();
    return 0;
}
