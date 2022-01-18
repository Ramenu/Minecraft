#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"

class Game
{
    public:
        Game(const unsigned int &windowWidth, const unsigned int &windowHeight);
        void startGame();
    private:
        void runGame();
        Window gameWindow;
        
};

#endif