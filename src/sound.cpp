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
    
    static std::pair<SoundData, SoundData> blockSounds[5] {
        std::pair<SoundData, SoundData>{"./sfx/grass/grassblockplace.wav", "./sfx/grass/grassblockbreak.wav"}, // Grass block sounds
        std::pair<SoundData, SoundData>{"./sfx/stone/stoneblockplace.wav", "./sfx/stone/stoneblockbreak.wav"}, // Stone block sounds
        std::pair<SoundData, SoundData>{"./sfx/wood/woodblockplace.wav", "./sfx/wood/woodblockbreak.wav"}, // Wood block sounds
        std::pair<SoundData, SoundData>{"./sfx/leaf/leafblockplace.wav", "./sfx/leaf/leafblockbreak.wav"}, // Leaf block sounds
        std::pair<SoundData, SoundData>{"./sfx/sand/sandblockplace.wav", "./sfx/sand/sandblockbreak.wav"} // Sand block sounds
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
        static constexpr int WOOD_BLOCK_SOUND_ID {2};
        static constexpr int LEAF_BLOCK_SOUND_ID {3};
        static constexpr int CACTUS_BLOCK_SOUND_ID {3};
        static constexpr int SAND_BLOCK_SOUND_ID {4};
        switch (name)
        {
            default: return STONE_BLOCK_SOUND_ID;
            case Grass_Block: return GRASS_BLOCK_SOUND_ID;
            case Dirt_Block: return DIRT_BLOCK_SOUND_ID;
            case OakWood_Block: return WOOD_BLOCK_SOUND_ID;
            case Leaf_Block: return LEAF_BLOCK_SOUND_ID;
            case Cactus_Block: return CACTUS_BLOCK_SOUND_ID;
            case Sand_Block: return SAND_BLOCK_SOUND_ID;
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