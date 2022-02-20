#include "mylib/game.hpp"
#include <memory>

int main()
{
    constexpr uint16_t windowWidth {400}, windowHeight {400};
    auto minecraft = std::make_unique<Game>(windowWidth, windowHeight);
    minecraft->runGame();
    return 0;
}
