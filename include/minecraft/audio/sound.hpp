#ifndef SOUND_HPP
#define SOUND_HPP

#include "minecraft/block/blockenum.hpp"

namespace Sound
{
    extern void playBlockPlacementSound(BlockName name) noexcept;
    extern void playBlockBreakSound(BlockName name) noexcept;
}

#endif // SOUND_HPP
