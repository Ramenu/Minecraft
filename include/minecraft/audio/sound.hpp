#ifndef MC_SOUND_HPP
#define MC_SOUND_HPP

#include "minecraft/block/blockenum.hpp"

namespace Sound
{
    extern void playBlockPlacementSound(BlockName name) noexcept;
    extern void playBlockBreakSound(BlockName name) noexcept;
}

#endif // MC_SOUND_HPP
