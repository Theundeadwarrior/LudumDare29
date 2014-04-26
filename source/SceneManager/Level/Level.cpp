#include "Level.h"
#include "GLM\include\glm\gtx\random.hpp"


namespace
{
	unsigned int GenerateRandomNumber(unsigned int min, unsigned int max)
	{
		return glm::linearRand(min, max);
	}

}

namespace Atum
{
namespace SceneManager
{

	Level::Level()
	{

	}

	LevelGenerator::LevelGenerator()
	{

	}

	LevelGenerator::~LevelGenerator()
	{

	}

	Atum::SceneManager::Level LevelGenerator::GenerateLevel(const Parameters& params, unsigned int currentHeight)
	{
		// If no height is specified, then we know that it's the first level generated which means we can randomly
		// choose the starting point of it
		if (currentHeight == INVALID_UNSIGNED_INT)
		{
			currentHeight = GenerateRandomNumber(0, params.LevelHeight - 2);
		}

		while (false)
		{

		}

		return Level();
	}
}

}