#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include <memory>

class Game
{
    public:
        Game(unsigned int windowWidth, unsigned int windowHeight);
        ~Game();
        void runGame();
        
};

#endif // GAME_HPP