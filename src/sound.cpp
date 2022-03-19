#include "minecraft/audio/sound.hpp"
#include "minecraft/audio/sounddata.hpp"

// An array that holds a pair of block sounds, the first element in the pair has a file path to the block's
// initialization sound. The second element contains a file path to the block's deletion sound. Examples of
// when these are played is when a player places or destroys a block.
static std::pair<SoundData, SoundData> blockSounds[2] {
    std::pair<SoundData, SoundData>{"./sfx/grassblock/grassplace.ogg", "./sfx/grassblock/grassbreak.ogg"}, // Grass block sounds
    std::pair<SoundData, SoundData>{"./sfx/stone/stoneplace.ogg", "./sfx/stone/stonebreak.ogg"} // Stone block sounds
};

/**
 * Plays the given block corresponding placement sound. 
 */
void playBlockPlacementSound(BlockName block)
{
    blockSounds[block].first.audio.play();
}   

/**
 * Plays the given block's corresponding deletion sound. 
 */
void playBlockBreakSound(BlockName block)
{
    blockSounds[block].second.audio.play();
}