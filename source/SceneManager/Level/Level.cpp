#include "Level.h"
#include "GLM\include\glm\gtx\random.hpp"
#include "Utilities\Debug\Debug.h"

namespace Atum
{
namespace SceneManager
{

	namespace
	{
		int GenerateRandomNumber(int min, int max)
		{
			return glm::ceil(glm::compRand1(float(min) - 0.5f, float(max) -0.5f));
		}
	}


	LevelLayout::LevelLayout(unsigned int width)
	{
		m_height.reserve(width);
	}

	void LevelLayoutGenerator::AddPlatform(LevelLayout& level, unsigned int height, unsigned int width)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			level.m_height.push_back(height);
		}
	}

	void LevelLayoutGenerator::AddJump(LevelLayout& level, unsigned int lenght)
	{
		for (unsigned i = 0; i < lenght; ++i)
		{
			level.m_height.push_back(JUMP_LEVEL_ID);
		}
	}


	LevelLayoutGenerator::LevelLayoutGenerator()
	{

	}

	LevelLayoutGenerator::~LevelLayoutGenerator()
	{

	}

	Atum::SceneManager::LevelLayout LevelLayoutGenerator::GenerateLevel(const Parameters& params, unsigned int startingHeight)
	{
		LevelLayout level(params.LevelWidth);
		unsigned int currentHeight = startingHeight;
		unsigned int totalLength = 0;

		// If no height is specified, then we know that it's the first level generated which means we can randomly
		// choose the starting point of it
		
		if (currentHeight == INVALID_UNSIGNED_INT)
		{
			currentHeight = GenerateRandomNumber(3, params.LevelHeight - 2);
		}


		while (level.GetLength() < params.LevelWidth)
		{
			// Add a new platform
			unsigned int length = GenerateRandomNumber(params.PlatformLenghtRange[0], params.PlatformLenghtRange[1]);
			if (totalLength + length >= params.LevelWidth)
			{
				length = params.LevelWidth - totalLength;
			}

			AddPlatform(level, currentHeight, length);
			totalLength += length;

			// Add new jump
			int jumpHeight = GetNextJumpHeight(currentHeight, params);
			int jumpLength = GetNextJumpLength(jumpHeight);

			if (totalLength + jumpLength >= params.LevelWidth)
			{
				jumpLength = 0;
			}

			AddJump(level, jumpLength);
			totalLength += jumpLength;
			currentHeight += jumpHeight;

		}

		return level;
	}

	int LevelLayoutGenerator::GetNextJumpHeight(unsigned int currentHeight, const Parameters &params)
	{
		int jumpHeight = 0;
		if (currentHeight + 2 >= params.LevelHeight)
		{
			jumpHeight = GenerateRandomNumber(-1, 0);
		}
		else if (jumpHeight + currentHeight < 0)
		{
			jumpHeight = GenerateRandomNumber(0, 1);
		}
		else
		{
			jumpHeight = GenerateRandomNumber(-1, 1);
		}

		return jumpHeight;
	}

	int LevelLayoutGenerator::GetNextJumpLength(int jumpHeight)
	{
		int jumpLength = 0;

		if (jumpHeight == -1)
		{
			jumpLength = GenerateRandomNumber(2, 8);
		}
		else if (jumpHeight == 0)
		{
			jumpLength = GenerateRandomNumber(2, 6);
		}
		else if (jumpHeight == 1)
		{
			jumpLength = GenerateRandomNumber(2, 4);
		}
		else
		{
			ATUM_ASSERT_MESSAGE(false, "Unmanaged jump height generated");
		}	return jumpLength;
	}

}
}