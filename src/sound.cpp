#include "minecraft/audio/sound.hpp"
#include "minecraft/audio/sounddata.hpp"

namespace Sound
{
    
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
        static constexpr int grassBlockSoundID {0},
                             stoneBlockSoundID {1};
        switch (name)
        {
            default: return grassBlockSoundID;
            case Cobblestone_Block: return stoneBlockSoundID;
            case Stone_Block: return stoneBlockSoundID;
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