#include "minecraft/world/worldgen.hpp"
#include "minecraft/world/perlin.hpp"
#include <cmath>

namespace WorldGen
{
	static constexpr int CHUNK_WIDTH_HALF {CHUNK_WIDTH / 2};
	static constexpr int CHUNK_LENGTH_HALF {CHUNK_WIDTH / 2};
	static constexpr int OAK_WOOD_MAXIMUM_HEIGHT {3}; // Maximum number of oak wood blocks a tree can have
	static constexpr int TREE_HEIGHT {OAK_WOOD_MAXIMUM_HEIGHT + 4};

	enum class TerrainTopFormat : std::uint8_t
	{
		Plains,
		Forest,
		Desert
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

	struct TreeInfo
	{
		bool formatCanSpawnTree {true};
		bool hasMaximumLimit {};
		std::uint8_t minimumTrees {};
		std::uint8_t maximumTrees {};
		int minimumRoll {};
	};
	static constexpr TreeInfo TREE_INFO_NULL {false, false, 0, 0, 0}; // Use if the biome cannot generate a tree


	/**
	 * Returns the tree layout/info for
	 * the given format.
	 */
	inline static constexpr TreeInfo getTreeLayout(TerrainTopFormat format) noexcept
	{
		switch (format)
		{
			default: return TreeInfo{.formatCanSpawnTree = true, .hasMaximumLimit = false, .minimumTrees = 0, .maximumTrees = 0, .minimumRoll = 397};

			case TerrainTopFormat::Forest: return TreeInfo{.formatCanSpawnTree = true, .hasMaximumLimit = true, 
			                                               .minimumTrees = 2, .maximumTrees = 4, .minimumRoll = 370};

			case TerrainTopFormat::Desert: return TREE_INFO_NULL;
		}
	}

	void initSeed() noexcept {
		std::srand(static_cast<unsigned int>(time(nullptr)));
	}


	static constexpr void spawnTreeAt(ChunkArray &chunk, glm::u8vec3 index) noexcept
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
	static constexpr void editChunk(ChunkArray &chunk, glm::u8vec3 portionSize, glm::u8vec3 currentIndex, Block block) noexcept
	{
		#ifndef NDEBUG
			assert(currentIndex.y < CHUNK_HEIGHT_HALF);
		#endif
		glm::u8vec3 offset {portionSize + currentIndex};
		if (offset.x + 1 >= CHUNK_WIDTH_HALF)
			offset.x = CHUNK_WIDTH_HALF - 1;
		if (offset.y + 1 >= CHUNK_HEIGHT_HALF)
			offset.y = CHUNK_HEIGHT_HALF - 1;
		if (offset.z + 1 >= CHUNK_LENGTH_HALF)
			offset.z = CHUNK_LENGTH_HALF - 1;
		for (std::int32_t x {currentIndex.x}; x < offset.x + 1; ++x)
			for (std::int32_t y {currentIndex.y}; y < offset.y + 1; ++y)
				for (std::int32_t z {currentIndex.z}; z < offset.z + 1; ++z)
					chunk[x][y][z] = block;

	}

	/**
	 * Returns a pseudo-randomized ore. The
	 * lower the 'y' coordinate is, the higher
	 * probability there will be to get rarer ores.
	 */
	static BlockName selectOrePick(std::uint32_t y) noexcept
	{
		static constexpr int NUM_TO_SPAWN_ORE {5};
		#ifndef NDEBUG
			assert(y < CHUNK_HEIGHT_HALF);
		#endif
		static constexpr struct {
			BlockName name;
			std::size_t maxRollSpawnRate;
			std::uint32_t minimumY;
		} oreSpawnRateProbabilities[] {
			{.name = IronOre_Block, .maxRollSpawnRate = 50, .minimumY = 5}, // Iron
			{.name = RedstoneOre_Block, .maxRollSpawnRate = 100, .minimumY = 4}, // Redstone
			{.name = GoldOre_Block, .maxRollSpawnRate = 100, .minimumY = 3}, // Gold
			{.name = DiamondOre_Block, .maxRollSpawnRate = 250, .minimumY = 2}, // Diamond
			{.name = EmeraldOre_Block, .maxRollSpawnRate = 500, .minimumY = 1} // Emerald
		};

		for (auto ore : oreSpawnRateProbabilities)
			if (std::rand() % ore.maxRollSpawnRate <= NUM_TO_SPAWN_ORE && y <= ore.minimumY)
				return ore.name;
		
		// If none of the ores spawned, then just spawn an ore block
		return CoalOre_Block;
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
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{3, 3, 3}
		};

		static constexpr std::array ironBlockCombinations {
			glm::u8vec3{1, 0, 1},
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{2, 2, 2},
		};

		static constexpr std::array goldBlockCombinations {
			glm::u8vec3{1, 0, 1},
			glm::u8vec3{1, 1, 1},
			glm::u8vec3{2, 2, 2}
		}; 

		static constexpr std::array diamondBlockCombinations {
			glm::u8vec3{1, 0, 0},
			glm::u8vec3{1, 0, 1},
			glm::u8vec3{2, 2, 2}
		};

		switch (ore)
		{
			default: return coalAndRedstoneBlockCombinations[std::rand() % coalAndRedstoneBlockCombinations.size()];
			case IronOre_Block: return ironBlockCombinations[std::rand() % ironBlockCombinations.size()];
			case GoldOre_Block: return goldBlockCombinations[std::rand() % goldBlockCombinations.size()];
			case DiamondOre_Block: return diamondBlockCombinations[std::rand() % diamondBlockCombinations.size()];
			case EmeraldOre_Block: return {0, 0, 1};
		}

	}

	/**
	 * Returns true if a tree can be spawned at the given position.
	 * Different formats may have different criteria for whether or not
	 * a tree should spawn.
	 */
	static bool canGenerateTree(const glm::i32vec3 &index, TerrainTopFormat format) noexcept
	{
		static constexpr int SPAWN_TREE_MAXIMUM_ROLL {400};
		const TreeInfo info {getTreeLayout(format)};

		if (!info.formatCanSpawnTree)
			return false;

		static std::uint32_t treesGenerated {};
		const auto roll {std::rand() % SPAWN_TREE_MAXIMUM_ROLL};
		bool spawnTree {(roll > info.minimumRoll) && (index.y + TREE_HEIGHT < CHUNK_HEIGHT)};
		if (info.hasMaximumLimit)
		{
			if (treesGenerated < info.minimumTrees && info.maximumTrees > treesGenerated)
			{
				spawnTree &= true;
				++treesGenerated;
			}
		}

		// Reset the # of trees generated, this is done so that the next time a
		// chunk is created the variable will reset itself.
		if (index.x == CHUNK_WIDTH - 1 && index.z == CHUNK_LENGTH - 1)
			treesGenerated = 0;

		return spawnTree;
	}

	/**
	 * Returns true if a cactus can be generated in
	 * the current position.
	 */
	static bool canGenerateCactus(TerrainTopFormat format) noexcept
	{
		static constexpr int SPAWN_CACTUS_MAXIMUM_ROLL {400};
		static constexpr int SPAWN_CACTUS_MINIMUM_ROLL {397};
		if (format != TerrainTopFormat::Desert) // Only deserts can generate cactuses
			return false;
		
		return (std::rand() % SPAWN_CACTUS_MAXIMUM_ROLL >= SPAWN_CACTUS_MINIMUM_ROLL);
	}

	/**
	 * Takes two coordinates 'x' and 'z' and outputs a
	 * y index created from perlin noise. 4 gradients should be used
	 * for each chunk for consistent and good-looking results.
	 * The 'maxHeight' parameter is simply the maximum y index that
	 * can be returned.
	 */
	static inline std::int32_t randomizeYIndex(float x, float z, 
	                                           const std::array<glm::vec2, 4UL> &gradients,
											   float maxHeight) noexcept
	{
		float noise {perlin(x, z, gradients)};

		// Transform range to [0.0, 1.0] assuming range of the noise is [-1.0, 1.0]
		noise += 1.0F;
		noise /= 2.0F;

		return static_cast<std::int32_t>(noise * maxHeight);

	}

	/**
	 * Generates the top half of the chunk.
	 * Takes the chunk as a parameter and the format of the chunk,
	 * which specifies the layout of the chunk and what blocks
	 * should be used.
	 */
	static void generateTopHalfOfChunk(std::pair<ChunkArray, std::uint8_t> &chunk,
	                                   TerrainFormat format) noexcept
	{
		float maxHeightForFormat {};
		float frequency {1.0F};
		std::int32_t highestY {};
		switch (format.topFormat)
		{
			case TerrainTopFormat::Plains: 
				maxHeightForFormat = 5.0F; 
				frequency = 6.0F;
				break;
			case TerrainTopFormat::Forest:
				maxHeightForFormat = static_cast<float>(2 + std::rand() % 2); // Randomize between 2 and 3
				frequency = 8.0F;
				break;
			case TerrainTopFormat::Desert:
				maxHeightForFormat = 4.0F;
				frequency = 6.0F;
				break;
		}
		static constexpr int MINIMUM_HEIGHT_LEVEL_FOR_TOP {CHUNK_HEIGHT_HALF};
		static constexpr int CACTUS_MAX_HEIGHT {2};
		static constexpr int CACTUS_MIN_HEIGHT {2};
		const auto gradients {generate2DGradients()};

		for (std::int32_t x {}; x < CHUNK_WIDTH; ++x)
		{
			for (std::int32_t z {}; z < CHUNK_LENGTH; ++z)
			{
				const float xf {static_cast<float>(x)};
				const float zf {static_cast<float>(z)};
				const std::int32_t topY {randomizeYIndex(xf * frequency, zf * frequency, gradients, maxHeightForFormat) + MINIMUM_HEIGHT_LEVEL_FOR_TOP};
				if (topY > highestY)
					highestY = topY;

				Block selectedBlock {format.mainBlock};
				if (canGenerateTree({x, topY, z}, format.topFormat)) 
				{
					highestY = std::min(CHUNK_HEIGHT - 1, highestY + TREE_HEIGHT);
					spawnTreeAt(chunk.first, {x, topY, z});
				}
				else if (canGenerateCactus(format.topFormat))
				{
					const auto cactusHeight {std::rand() % CACTUS_MAX_HEIGHT + CACTUS_MIN_HEIGHT};
					if (topY + cactusHeight < CHUNK_HEIGHT)
					{
						if (topY + cactusHeight > highestY)
							highestY = topY + cactusHeight;
						// Spawn a cactus at the position
						for (std::int32_t y {topY}; y <= topY + cactusHeight; ++y)
							chunk.first[x][y][z] = Block{Cactus_Block};
					}
				}
				for (std::int32_t y {topY}; y >= MINIMUM_HEIGHT_LEVEL_FOR_TOP; --y)
				{
					chunk.first[x][y][z] = selectedBlock;
					selectedBlock = format.secondaryBlock;
				}
			}
		}
		chunk.second = static_cast<std::uint8_t>(highestY) + 1;
		#ifndef NDEBUG
			assert(chunk.second <= CHUNK_HEIGHT);
		#endif
	}

	/**
	 * Should be immediately called when dealing with the lower parts of the chunk
	 * (i.e., any y component lower than CHUNK_HEIGHT_HALF). Handles ore generation
	 */
	static void generateBottomHalfOfChunk(ChunkArray &chunk, int yEnd) noexcept
	{
		#ifndef NDEBUG
			assert(yEnd <= CHUNK_HEIGHT_HALF);
		#endif
		static constexpr std::uint32_t MAXIMUM_NUM {100};
		static constexpr Block stoneBlock {Stone_Block};
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

					// Spawn a ore if the percent is between 95 and 100
					if (randomPercent >= 95 && randomPercent <= 100)
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
    static void generatePlainsBiome(std::pair<ChunkArray, std::uint8_t> &chunk) noexcept
	{
		const TerrainFormat format {
			.mainBlock = Block{Grass_Block},
			.secondaryBlock = Block{Dirt_Block},
			.topFormat = TerrainTopFormat::Plains
		};
		generateTopHalfOfChunk(chunk, format);
		generateBottomHalfOfChunk(chunk.first, CHUNK_HEIGHT_HALF);
	}

	/**
	 * Modifies the chunk to make it look like a forest biome.
	 */
    static void generateForestBiome(std::pair<ChunkArray, std::uint8_t> &chunk) noexcept
	{
		const TerrainFormat format {
			.mainBlock = Block{Grass_Block},
			.secondaryBlock = Block{Dirt_Block},
			.topFormat = TerrainTopFormat::Forest
		};
		generateTopHalfOfChunk(chunk, format);
		generateBottomHalfOfChunk(chunk.first, CHUNK_HEIGHT_HALF);
	}

	static void generateDesertBiome(std::pair<ChunkArray, std::uint8_t> &chunk) noexcept
	{
		const TerrainFormat format {
			.mainBlock = Block{Sand_Block},
			.secondaryBlock = Block{Sand_Block},
			.topFormat = TerrainTopFormat::Desert
		};
		generateTopHalfOfChunk(chunk, format);
		generateBottomHalfOfChunk(chunk.first, CHUNK_HEIGHT_HALF);
	}

	/**
	 * Generates a terrain of the given biome, and returns a pair
	 * with the first member being the chunk with biome's terrain.
	 * The second param is the maximum height of the chunk.
	 */
    std::pair<ChunkArray, std::uint8_t> generateTerrain(Biome biome) noexcept 
    {
		std::pair<ChunkArray, std::uint8_t> chunk {};
		#if 1
		switch (biome)
		{
			case Plains: generatePlainsBiome(chunk); break;
			case Forest: generateForestBiome(chunk); break;
			case Desert: generateDesertBiome(chunk); break;
		}
		#else
			if (biome == Plains || biome == Forest)
			{
				for (std::uint32_t x {}; x < CHUNK_WIDTH; ++x)
					for (std::uint32_t y {}; y < CHUNK_HEIGHT; ++y)
						for (std::uint32_t z {}; z < CHUNK_LENGTH; ++z)
							chunk.first[x][y][z] = Block{Grass_Block};
			}

		#endif
		return chunk;
    }

}


