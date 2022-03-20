#ifndef SOUND_HPP
#define SOUND_HPP

#include "minecraft/block/blockenum.hpp"

extern void playBlockPlacementSound(BlockSoundID id) noexcept;
extern void playBlockBreakSound(BlockSoundID id) noexcept;

#endif // SOUND_HPP
