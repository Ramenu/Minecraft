#include "minecraft/world/worldgen.hpp"
#include "minecraft/world/perlin.hpp"
#include <cmath>

namespace WorldGen
{
	static constexpr int CHUNK_WIDTH_HALF {CHUNK_WIDTH / 2};
	static constexpr int CHUNK_HEIGHT_HALF {CHUNK_HEIGHT / 2};
	static constexpr int CHUNK_LENGTH_HALF {CHUNK_WIDTH / 2};
	static constexpr int OAK_WOOD_MAXIMUM_HEIGHT {3}; // Maximum number of oak wood blocks a tree can have
	static constexpr int TREE_HEIGHT {OAK_WOOD_MAXIMUM_HEIGHT + 4};

	enum class TerrainTopFormat : std::uint8_t
	{
		Standard // No peculiar features
	};

	enum class TerrainMidFormat : std::uint8_t
	{
		Standard // No peculiar features (to be defined)
	};

	struct TerrainFormat
	{
		Block mainBlock;
		Block secondaryBlock;
		union
		{
			TerrainTopFormat topFormat;
			TerrainMidFormat midFormat;
		};
	};

	void initSeed() noexcept
	{
		std::srand(time(nullptr));

	}

	/**
	 * Fills the chunk with air blocks.
	 * TODO: Later on try to find a way to optimize this.
	 */
	static constexpr std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> fillChunkWithAirBlocks() noexcept {
		std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> chunk;
		for (std::int32_t y {CHUNK_HEIGHT - 1}; y >= 0; --y)
			for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
				for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
					chunk[x][y][z] = Block{Air_Block};
		return chunk;
	}

	static constexpr void spawnTreeAt(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk,
	                                  glm::u8vec3 index) noexcept
	{

		const std::int32_t treeOffset {index.y + TREE_HEIGHT};
		const bool treeOnEdgesOfChunk {((index.x + 2 >= CHUNK_WIDTH) || (index.z + 2 >= CHUNK_LENGTH)) ||
		                               ((index.x - 2 < 0) || (index.z - 2 < 0))};

		// Only build the tree if there is enough space in the chunk to do so, and not on the edges of the chunk
		if ((treeOffset < CHUNK_HEIGHT) && (!treeOnEdgesOfChunk))
		{
			const auto yTopWood {index.y + OAK_WOOD_MAXIMUM_HEIGHT + 1};

			// Build the oak blocks
			for (std::int32_t y {index.y}; y < yTopWood; ++y)
				chunk[index.x][y][index.z] = Block{OakWood_Block};
			
			// First layer of leaves
			for (std::int32_t x {index.x - 2}; x < index.x + 3; ++x)
				for (std::int32_t z {index.z - 2}; z < index.z + 3; ++z)
					chunk[x][yTopWood][z] = Block{Leaf_Block};
			
			// Remove edges of first layer
			chunk[index.x - 2][yTopWood][index.z + 2] = Block{Air_Block};
			chunk[index.x - 2][yTopWood][index.z - 2] = Block{Air_Block};
			chunk[index.x + 2][yTopWood][index.z - 2] = Block{Air_Block};
			chunk[index.x + 2][yTopWood][index.z + 2] = Block{Air_Block};
			#if 1
			// Second layer of leaves
			for (std::int32_t x {index.x - 1}; x < index.x + 2; ++x)
				for (std::int32_t z {index.z - 1}; z < index.z + 2; ++z)
					chunk[x][yTopWood + 1][z] = Block{Leaf_Block};
			
			// Last layer of leaves (i.e., top layer)
			for (std::int32_t x {index.x}; x < index.x + 1; ++x)
				for (std::int32_t z {index.z}; z < index.z + 1; ++z)
					chunk[x][yTopWood + 2][z] = Block{Leaf_Block};
			#endif
			
		}

	}

	/**
	 * A function for editing a portion of a chunk. The 'portionSize' should be the
	 * bounding volume of the block you want to emplace (e.g. create 4x4x4 coal blocks).
	 * The current index lets the function know where to emplace those blocks specifically.
	 * 
	 * NOTE: This should only be used for generating the bottom parts of the chunk, this
	 * does not account for out-of-bounds access.
	 * 
	 * For better locality, it is recommended that all of the components in the portion size
	 * be the same.
	 */
	static constexpr void editChunk(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk,
	                      glm::u8vec3 portionSize,
						  glm::u8vec3 currentIndex,
						  Block block) noexcept
	{
		#ifndef NDEBUG
			if (currentIndex.y >= CHUNK_HEIGHT_HALF)
			{
				//printf("editChunk called with illegal y-indice: %d\n", currentIndex.y);
				exit(EXIT_FAILURE);
			}

		#endif
		glm::u8vec3 offset {portionSize + currentIndex};
		if (offset.x >= CHUNK_WIDTH_HALF) offset.x = CHUNK_WIDTH_HALF - 1;
		if (offset.y >= CHUNK_HEIGHT_HALF) offset.y = CHUNK_HEIGHT_HALF - 1;
		if (offset.z >= CHUNK_LENGTH_HALF) offset.z = CHUNK_LENGTH_HALF - 1;
		for (std::int32_t x {currentIndex.x}; x < offset.x; ++x)
			for (std::int32_t y {currentIndex.y}; y < offset.y; ++y)
				for (std::int32_t z {currentIndex.z}; z < offset.z; ++z)
					chunk[x][y][z] = block;

	}

	/**
	 * Returns a pseudo-randomized ore. The
	 * lower the 'y' coordinate is, the higher
	 * probability there will be to get rarer ores.
	 */
	static BlockName selectOrePick(std::uint32_t y) noexcept
	{
		#ifndef NDEBUG
			if (y >= 8)
			{
				printf("selectOrePick invalid pick!!!: %d\n", y);
				exit(-12);
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

	/**
	 * Returns a pseudo-randomized portion. Each ore
	 * may have an exclusive set of combinations. Rarer
	 * ores will have smaller portions whereas common ores
	 * will have larger portions. 
	 */
	static glm::u8vec3 getOrePortionSize(BlockName ore) noexcept
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
	 * Takes two coordinates 'x' and 'z' and outputs a
	 * y index created from perlin noise. 4 gradients should be used
	 * for each chunk for consistent and good-looking results.
	 * The 'maxHeight' parameter is simply the maximum y index that
	 * can be returned.
	 */
	static inline std::int32_t randomizeYIndex(std::int32_t x, std::int32_t z, 
	                                           const std::array<glm::vec2, 4> &gradients,
											   std::uint32_t maxHeight) noexcept
	{
		float noise {perlin(x, z, gradients)};

		// Transform range to [0.0, 1.0] assuming range of the noise is [-1.0, 1.0]
		noise += 1.0f;
		noise /= 2.0f;

		return static_cast<std::int32_t>(noise * maxHeight);

	}

	/**
	 * Generates the top half of the chunk.
	 * Takes the chunk as a parameter and the format of the chunk,
	 * which specifies the layout of the chunk and what blocks
	 * should be used.
	 */
	static void generateTopHalfOfChunk(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk,
	                                   TerrainFormat format) noexcept
	{
		#if 1
		std::int32_t maxHeightForFormat {};
		float frequency {1.0f};
		bool formatCanSpawnTree {true};
		switch (format.topFormat)
		{
			case TerrainTopFormat::Standard: 
				maxHeightForFormat = 4; 
				frequency = 5.0f;
				break;
		}
		static constexpr int MINIMUM_HEIGHT_LEVEL_FOR_TOP {CHUNK_HEIGHT_HALF};
		static constexpr int SPAWN_TREE_MAXIMUM_ROLL {100};
		static constexpr int MIN_ROLL_TO_SPAWN_TREE {98};
		const auto gradients {generate2DGradients()};
		for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
		{
			for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
			{
				std::int32_t yIndex {randomizeYIndex(x * frequency, z * frequency, gradients, maxHeightForFormat) + MINIMUM_HEIGHT_LEVEL_FOR_TOP};
				const bool spawnTree {(std::rand() % SPAWN_TREE_MAXIMUM_ROLL > MIN_ROLL_TO_SPAWN_TREE) && (yIndex + TREE_HEIGHT < CHUNK_HEIGHT)};
				Block selectedBlock {format.mainBlock};
				if (spawnTree&formatCanSpawnTree)
				{
					spawnTreeAt(chunk, {x, yIndex, z});
					yIndex -= 1;
				}
				for (std::int32_t y {yIndex}; y >= MINIMUM_HEIGHT_LEVEL_FOR_TOP; --y)
				{
					chunk[x][y][z] = selectedBlock;
					selectedBlock = format.secondaryBlock;
				}
			}
		}
		#endif
	}

	/**
	 * Should be immediately called when dealing with the lower parts of the chunk
	 * (i.e., any y component lower than CHUNK_HEIGHT_HALF). Handles ore generation
	 */
	static void generateBottomHalfOfChunk(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk, int yEnd) noexcept
	{
		#ifndef NDEBUG
			if (!(yEnd <= 8))
			{
				printf("ERROR: At 'generateBottomHalfOfChunk' y's value is %d!\n", yEnd);
				exit(EXIT_FAILURE);
			}
		#endif
		static constexpr std::uint32_t MAXIMUM_NUM {100};
		static constexpr Block stoneBlock {Stone_Block};
		static constexpr glm::u8vec3 STONE_BLOCK_PORTION {4, 4, 4};
		glm::u8vec3 portion;
		for (std::int32_t y {}; y < yEnd; ++y)
		{
			for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
			{
				for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
				{
					chunk[x][y][z] = Block{Stone_Block};
					const glm::u8vec3 index {x, y, z};
					const std::uint32_t randomPercent {std::rand() % MAXIMUM_NUM + 1};
					if (randomPercent >= 90 && randomPercent <= 100)
					{
						const BlockName ore {selectOrePick(y)};
						editChunk(chunk, getOrePortionSize(ore), index, Block{ore});
					}
					else
						editChunk(chunk, portion, index, stoneBlock);
				}
			}
		}
	}
	

	/**
	 * Modifies the chunk to make it look like a plains biome.
	 */
    static void generatePlainsBiome(std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> &chunk) noexcept
	{
		const TerrainFormat format {
			.mainBlock = Block{Grass_Block},
			.secondaryBlock = Block{Dirt_Block},
			.topFormat = TerrainTopFormat::Standard
		};
		generateTopHalfOfChunk(chunk, format);
		generateBottomHalfOfChunk(chunk, CHUNK_HEIGHT_HALF);
	}

	/**
	 * Generates a terrain of the given biome, and returns a chunk
	 * with the new terrain.
	 */
    std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> generateTerrain(Biome biome) noexcept 
    {
		std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_HEIGHT>, CHUNK_LENGTH> chunk {fillChunkWithAirBlocks()};
		switch (biome)
		{
			case Plains: generatePlainsBiome(chunk); break;
		}
		return chunk;
    }

}


