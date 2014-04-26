#include "Level.h"
#include "GLM\include\glm\gtx\random.hpp"

namespace Atum
{
namespace SceneManager
{

	namespace
	{
		unsigned int GenerateRandomNumber(unsigned int min, unsigned int max)
		{
			return glm::compRand1(min, max);
		}
	}


	Level::Level(unsigned int width)
	{
		m_height.reserve(width);
	}

	void Level::AddPlatform(unsigned int height, unsigned int width)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			m_height.push_back(height);
		}
	}

	LevelGenerator::LevelGenerator()
	{

	}

	LevelGenerator::~LevelGenerator()
	{

	}

	Atum::SceneManager::Level LevelGenerator::GenerateLevel(const Parameters& params, unsigned int startingHeight)
	{
		Level level(params.LevelWidth);
		unsigned int currentHeight = startingHeight;

		// If no height is specified, then we know that it's the first level generated which means we can randomly
		// choose the starting point of it
		
		if (currentHeight == INVALID_UNSIGNED_INT)
		{
			currentHeight = GenerateRandomNumber(0, params.LevelHeight - 2);
		}

		while (level.GetWidth() < params.LevelWidth)
		{
			unsigned int length = GenerateRandomNumber(params.PlatformLenghtRange[0], params.PlatformLenghtRange[1]);
			level.AddPlatform(currentHeight, length);
		}

		return level;
	}
}

}