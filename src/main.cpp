#include "mylib/game.hpp"
#include <memory>

int main()
{
    static_assert(sizeof(size_t) >= 4, "Integer must be at least 4 bytes to run program.");
    constexpr uint16_t windowWidth {400}, windowHeight {400};
    auto minecraft = std::make_unique<Game>(windowWidth, windowHeight);
    minecraft->runGame();
    return 0;
}
