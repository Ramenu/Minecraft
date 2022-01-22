#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include <memory>

class Game
{
    public:
        Game(const unsigned int &windowWidth, const unsigned int &windowHeight);
        void startGame();
    private:
        void runGame();
        std::unique_ptr<Window> gameWindow;
        
};

#endif