#include "minecraft/audio/sound.hpp"

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

namespace Sound
{
    class SoundData
    {
        public:
            explicit inline SoundData(const std::string &soundFilePath) noexcept
            {
                buffer.loadFromFile(soundFilePath);
                audio.setBuffer(buffer);
            }
            sf::Sound audio;
        private:
            sf::SoundBuffer buffer;
    };
    
    static std::pair<SoundData, SoundData> blockSounds[2] {
        std::pair<SoundData, SoundData>{"./sfx/grassblock/grassplace.ogg", "./sfx/grassblock/grassbreak.ogg"}, // Grass block sounds
        std::pair<SoundData, SoundData>{"./sfx/stone/stoneplace.ogg", "./sfx/stone/stonebreak.ogg"} // Stone block sounds
    };

    /**
     * Returns the sound ID of the block.
     * Some blocks may share similar sounds, so
     * the enum cannot be used directly. That is why
     * this function exists.
     */
    static uint8_t getSoundID(BlockName name) noexcept
    {
        static constexpr int GRASS_BLOCK_SOUND_ID {0};
        static constexpr int DIRT_BLOCK_SOUND_ID {0};
        static constexpr int STONE_BLOCK_SOUND_ID {1};
        switch (name)
        {
            case Grass_Block: return GRASS_BLOCK_SOUND_ID;
            case Dirt_Block: return DIRT_BLOCK_SOUND_ID;
            default: return STONE_BLOCK_SOUND_ID;
        }
    }

    /**
     * Plays the block's sound on creation.
     */
    void playBlockPlacementSound(BlockName name) noexcept
    {
        blockSounds[getSoundID(name)].first.audio.play();
    }
    
    /**
     * Plays the block's destruction sound.
     */
    void playBlockBreakSound(BlockName name) noexcept
    {
        blockSounds[getSoundID(name)].second.audio.play();
    }
}