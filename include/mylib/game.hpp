#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include <memory>

class Game
{
    public:
        Game(const unsigned int windowWidth, const unsigned int windowHeight);
        ~Game();
        void runGame();
        
};

#endif // GAME_HPP