#ifndef SOUND_HPP
#define SOUND_HPP

#include "minecraft/block/blockenum.hpp"
#include "sounddata.hpp"

namespace Sound
{
    // An array that holds a pair of block sounds, the first element in the pair has a file path to the block's
    // initialization sound. The second element contains a file path to the block's deletion sound. Examples of
    // when these are played is when a player places or destroys a block.
    inline std::pair<SoundData, SoundData> blockSounds[2] {
        std::pair<SoundData, SoundData>{"./sfx/grassblock/grassplace.ogg", "./sfx/grassblock/grassbreak.ogg"}, // Grass block sounds
        std::pair<SoundData, SoundData>{"./sfx/stone/stoneplace.ogg", "./sfx/stone/stonebreak.ogg"} // Stone block sounds
    };

    inline void playBlockPlacementSound(BlockSoundID id) noexcept
    {
        blockSounds[id].first.audio.play();
    }
    inline void playBlockBreakSound(BlockSoundID id) noexcept
    {
        blockSounds[id].second.audio.play();
    }
}

#endif // SOUND_HPP
