#include "mylib/game.hpp"

int main()
{
    static_assert(sizeof(size_t) >= 4, "Integer must be at least 4 bytes to run program.");
    constexpr uint16_t windowWidth {400}, windowHeight {400};
    Game minecraft {windowWidth, windowHeight};
    minecraft.runGame();
    return 0;
}
