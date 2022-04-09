#ifndef SOUND_HPP
#define SOUND_HPP

#include "minecraft/block/blockenum.hpp"

namespace Sound
{
    extern void playBlockPlacementSound(BlockName name);
    extern void playBlockBreakSound(BlockName name);
}

#endif // SOUND_HPP
