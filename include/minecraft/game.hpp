#ifndef GAME_HPP
#define GAME_HPP

class Game
{
    public:
        explicit Game(const char *windowTitle);
        Game(const Game &game) = delete;
        Game(Game &&game) = delete;
        ~Game() noexcept;
        void runGame();
};

#endif // GAME_HPP