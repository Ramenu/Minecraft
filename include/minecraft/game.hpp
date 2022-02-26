#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>

class Game
{
    public:
        Game(uint16_t windowWidth, uint16_t windowHeight);
        ~Game();
        void runGame();
        
};

#endif // GAME_HPP