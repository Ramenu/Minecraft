#include "minecraft/game.hpp"

int main()
{
    static_assert(sizeof(size_t) >= 4, "Go buy a real computer");
    constexpr uint16_t windowWidth {512}, windowHeight {512};
    Game minecraft {windowWidth, windowHeight};
    minecraft.runGame();
    return 0;
}
