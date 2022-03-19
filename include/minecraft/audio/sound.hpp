#ifndef SOUND_HPP
#define SOUND_HPP

#include "minecraft/block/blockname.hpp"

extern void playBlockPlacementSound(BlockName block) noexcept;
extern void playBlockBreakSound(BlockName block) noexcept;

#endif // SOUND_HPP
