#include "minecraft/audio/sound.hpp"
#include "minecraft/audio/sounddata.hpp"

// An array that holds a pair of block sounds, one which holds the sound of the block on creation, and the second
// holds the deletion sound
std::pair<SoundData, SoundData> blockSounds[2] {
    std::pair<SoundData, SoundData>{"./sfx/grassblock/grassplace.ogg", "./sfx/grassblock/grassbreak.ogg"}, // Grass block sounds
    std::pair<SoundData, SoundData>{"./sfx/stone/stoneplace.ogg", "./sfx/stone/stonebreak.ogg"} // Stone block sounds
};

/* Plays the given block name's corresponding placement sound. */
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

/* Plays the given block name's corresponding deletion sound. */
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