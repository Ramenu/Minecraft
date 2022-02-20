#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include <cstdint>
#include <memory>

class Game
{
    public:
        explicit Game(uint16_t windowWidth, uint16_t windowHeight);
        ~Game();
        void runGame();
        
};

#endif // GAME_HPP