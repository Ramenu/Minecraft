#ifndef SOUNDDATA_HPP
#define SOUNDDATA_HPP

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wsuggest-override"
    #pragma GCC diagnostic ignored "-Wuseless-cast"
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    #include "SFML/Audio.hpp"
    #pragma GCC diagnostic pop
#else
    #include "SFML/Audio.hpp"
#endif

class SoundData
{
    public:
        explicit SoundData(const std::string &soundFilePath) noexcept;
        sf::Sound audio;
    private:
        sf::SoundBuffer buffer;
};

#endif // SOUNDDATA_HPP
