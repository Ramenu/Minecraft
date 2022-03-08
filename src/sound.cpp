#include "minecraft/audio/sound.hpp"
#include "minecraft/audio/sounddata.hpp"

// An array that holds a pair of block sounds, the first element in the pair has a file path to the block's
// initialization sound. The second element contains a file path to the block's deletion sound. Examples of
// when these are played is when a player places or destroys a block.
std::pair<SoundData, SoundData> blockSounds[2] {
    std::pair<SoundData, SoundData>{"./sfx/grassblock/grassplace.ogg", "./sfx/grassblock/grassbreak.ogg"}, // Grass block sounds
    std::pair<SoundData, SoundData>{"./sfx/stone/stoneplace.ogg", "./sfx/stone/stonebreak.ogg"} // Stone block sounds
};

/**
 * Plays the given block corresponding placement sound. 
 */
void playBlockPlacementSound(BlockName block)
{
    using Block = BlockName;
    switch (block)
    {
        default: /* Throw exception */ break;
        case Block::Grass_Block: blockSounds[0].first.audio.play(); break;
        case Block::Cobblestone_Block: blockSounds[1].first.audio.play(); break;
    }
}   

/**
 * Plays the given block's corresponding deletion sound. 
 */
void playBlockBreakSound(BlockName block)
{
    using Block = BlockName;
    switch (block)
    {
        default: /* Throw exception */ break;
        case Block::Grass_Block: blockSounds[0].second.audio.play(); break;
        case Block::Cobblestone_Block: blockSounds[1].second.audio.play(); break;
    }
}