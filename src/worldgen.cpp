#include "minecraft/worldgen.hpp"
#include <algorithm>

namespace WorldGen
{
	static constexpr int CHUNK_HEIGHT_HALF {CHUNK_HEIGHT / 2};

	/**
	 * A function for editing a portion of a chunk. The 'portionSize' should be the
	 * bounding volume of the block you want to emplace (e.g. create 4x4x4 coal blocks).
	 * The current index lets the function know where to emplace those blocks specifically.
	 * 
	 * This function takes care of out-of-bounds access, HOWEVER it does assume that the
	 * current index is less than the chunk's maximum x, y, z components. Do not call this
	 * function if any of them are out of bounds (though, with proper use they shouldn't be
	 * in the first place).
	 * 
	 * For better locality, it is recommended that all of the components in the portion size
	 * be the same.
	 */
	#if 1
	static void editChunk(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk,
	                      glm::u8vec3 portionSize,
						  glm::u8vec3 currentIndex,
						  Block block)
	{
		glm::u8vec3 offset {portionSize + currentIndex};
		if (offset.x > CHUNK_WIDTH) offset.x = CHUNK_WIDTH;
		if (offset.y > CHUNK_HEIGHT) offset.y = CHUNK_HEIGHT;
		if (offset.z > CHUNK_LENGTH) offset.z = CHUNK_LENGTH;
		for (std::int32_t x {currentIndex.x}; x < offset.x; ++x)
			for (std::int32_t y {currentIndex.y}; y < offset.y; ++y)
				for (std::int32_t z {currentIndex.z}; z < offset.z; ++z)
					chunk[x][y][z] = block;

	}
	#endif

	static BlockName selectOrePick(std::uint32_t y)
	{
		#ifndef NDEBUG
			if (y >= 8)
			{
				printf("selectOrePick invalid pick!!!");
				exit(EXIT_FAILURE);
			}
		#endif
		const std::uint32_t rarity {CHUNK_HEIGHT_HALF - y}; // Higher is better
		static constexpr BlockName oresToChooseFrom[] {
			CoalOre_Block, CoalOre_Block,
			IronOre_Block, IronOre_Block,
			GoldOre_Block,
			RedstoneOre_Block,
			DiamondOre_Block,
			EmeraldOre_Block
		};
		if (rarity == 0) // To avoid floating-point exception
			return oresToChooseFrom[0];
		
		const auto randomSelect {std::rand() % rarity};
		#ifndef NDEBUG
			if (randomSelect >= 8)
			{
				printf("ERROR: INVALID RANDOM\n");
				exit(-1);
			}

		#endif
 		return oresToChooseFrom[randomSelect];
	}

	static glm::u8vec3 getOrePortionSize(BlockName ore)
	{
		static constexpr std::array coalAndRedstoneBlockCombinations {
			glm::u8vec3{2, 2, 2},
			glm::u8vec3{2, 2, 0},
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{3, 3, 3}
		};

		static constexpr std::array ironBlockCombinations {
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{2, 0, 2},
			glm::u8vec3{2, 2, 2},
			glm::u8vec3{1, 1, 0}
		};

		static constexpr std::array goldBlockCombinations {
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{2, 2, 2}
		}; 

		static constexpr std::array diamondBlockCombinations {
			glm::u8vec3{1, 0, 0},
			glm::u8vec3{0, 0, 1},
			glm::u8vec3{1, 0, 1},
			glm::u8vec3{2, 2, 2}
		};

		switch (ore)
		{
			default: return coalAndRedstoneBlockCombinations[std::rand() % coalAndRedstoneBlockCombinations.size()];
			case IronOre_Block: return ironBlockCombinations[std::rand() % ironBlockCombinations.size()];
			case GoldOre_Block: return goldBlockCombinations[std::rand() % goldBlockCombinations.size()];
			case DiamondOre_Block: return diamondBlockCombinations[std::rand() % diamondBlockCombinations.size()];
			case EmeraldOre_Block: return {1, 0, 0};
		}

	}

	/**
	 * Should be immediately called when dealing with the lower parts of the chunk
	 * (i.e., any y component lower than CHUNK_HEIGHT_HALF). Handles ore generation
	 */
	static void generateBottomHalfOfChunk(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk)
	{
		static constexpr std::uint32_t MAXIMUM_NUM {100};
		static constexpr Block stoneBlock {Stone_Block};
		static constexpr glm::u8vec3 STONE_BLOCK_PORTION {4, 4, 4};
		glm::u8vec3 portion;
		for (std::int32_t y {CHUNK_HEIGHT_HALF - 1}; y >= 0; --y)
		{
			for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
			{
				for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
				{
					chunk[x][y][z] = Block{Stone_Block};
					const glm::u8vec3 index {x, y, z};
					const std::uint32_t randomPercent {std::rand() % MAXIMUM_NUM + 1};
					if (randomPercent >= 1 && randomPercent <= 95)
						editChunk(chunk, portion, STONE_BLOCK_PORTION, stoneBlock);
					else
					{
						const BlockName ore {selectOrePick(y)};
						editChunk(chunk, getOrePortionSize(ore), index, Block{ore});
					}
				}
			}
		}
		
	}

    static std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> generatePlainsBiome() noexcept
	{
		std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> chunk;

		Block selectedBlock {Grass_Block};
		for (std::int32_t y {CHUNK_HEIGHT - 1}; y >= CHUNK_HEIGHT_HALF; --y)
		{
			for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
				for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
					chunk[x][y][z] = selectedBlock;
			selectedBlock = Block{Dirt_Block};
		}
		generateBottomHalfOfChunk(chunk);
		return chunk;
	}

    std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> generateTerrain(Biome biome) noexcept 
    {
		switch (biome)
		{
			case Biome::Plains: return generatePlainsBiome();
		}
		return generatePlainsBiome();
    }

}


