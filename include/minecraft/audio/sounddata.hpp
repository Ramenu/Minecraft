#ifndef SOUNDDATA_HPP
#define SOUNDDATA_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wuseless-cast"
#include "SFML/Audio.hpp"
#pragma GCC diagnostic pop

class SoundData
{
    public:
        explicit SoundData(const char* soundFilePath);
        sf::Sound audio;
        sf::SoundBuffer buffer;
};

#endif // SOUNDDATA_HPP
