#include "Level.h"
#include "GLM\include\glm\gtx\random.hpp"
#include "Utilities\Debug\Debug.h"
#include <fstream>

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

	LevelLayoutGenerator::Parameters::Parameters()
		: BridgeProbability(0.2f)
		, IsUnderGround(false)
	{

	}

	LevelLayout::LevelLayout(unsigned int width)
	{
	}

	void LevelLayoutGenerator::AddPlatform(LevelLayout& level, unsigned int height, unsigned int width)
	{

		level.m_platforms.push_back(PlatformInfo(m_params.IsUnderGround ? PlatformInfo::E_Ruins : PlatformInfo::E_Canyon, height, width));
	}

	void LevelLayoutGenerator::AddJump(LevelLayout& level, unsigned int lenght)
	{
		level.m_platforms.push_back(PlatformInfo(PlatformInfo::E_Jump, 0, lenght));
	}


	LevelLayoutGenerator::LevelLayoutGenerator(const Parameters& params)
	{
		m_params = params;
	}

	LevelLayoutGenerator::~LevelLayoutGenerator()
	{

	}

	Atum::SceneManager::LevelLayout LevelLayoutGenerator::GenerateLevel(unsigned int startingHeight)
	{
		LevelLayout level(m_params.LevelWidth);
		unsigned int currentHeight = startingHeight;
		unsigned int totalLength = 0;

		// If no height is specified, then we know that it's the first level generated which means we can randomly
		// choose the starting point of it
		if (currentHeight == INVALID_UNSIGNED_INT)
		{
			currentHeight = GenerateRandomNumber(3, m_params.LevelHeight - 2);
		}

		while (totalLength < m_params.LevelWidth)
		{
			// Add a new platform
			unsigned int length = GenerateRandomNumber(m_params.PlatformLenghtRange[0], m_params.PlatformLenghtRange[1]);
			if (totalLength + length >= m_params.LevelWidth)
			{
				length = m_params.LevelWidth - totalLength;
			}

			AddPlatform(level, currentHeight, length);
			totalLength += length;

			// Add new jump
			int jumpHeight = GetNextJumpHeight(currentHeight, m_params);
			int jumpLength = GetNextJumpLength(jumpHeight);

			if (totalLength + jumpLength >= m_params.LevelWidth)
			{
				jumpLength = 0;
			}

			AddJump(level, jumpLength);
			totalLength += jumpLength;
			currentHeight += jumpHeight;

		}

		// try placing new bridges when 2 platforms have the same height
		GenerateBridge(level);

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
			jumpLength = GenerateRandomNumber(4, 9);
		}
		else if (jumpHeight == 0)
		{
			jumpLength = GenerateRandomNumber(4, 8);
		}
		else if (jumpHeight == 1)
		{
			jumpLength = GenerateRandomNumber(2, 4);
		}
		else
		{
			ATUM_ASSERT_MESSAGE(false, "Unmanaged jump height generated");
		}	
		return jumpLength;
	}

	void LevelLayoutGenerator::GenerateBridge(LevelLayout& levelLayout)
	{
		// New data
		for (int i = 0; i + 2 < levelLayout.m_platforms.size(); ++i)
		{
			if (levelLayout.m_platforms[i].Type != PlatformInfo::E_Jump && levelLayout.m_platforms[i + 1].Type == PlatformInfo::E_Jump
				&& levelLayout.m_platforms[i + 2].Type != PlatformInfo::E_Jump && levelLayout.m_platforms[i].Height == levelLayout.m_platforms[i + 2].Height)
			{
				CreateBridge(levelLayout, i+1);
			}
		}
	}

	void LevelLayoutGenerator::CreateBridge(LevelLayout& level, unsigned int indexOfPlatform)
	{
		int randomNumber = GenerateRandomNumber(0, 100);

		if (randomNumber < m_params.BridgeProbability * 100)
		{
			level.m_platforms[indexOfPlatform].Type = PlatformInfo::E_Bridge;
			level.m_platforms[indexOfPlatform].Height = level.m_platforms[indexOfPlatform - 1].Height;
		}
	}

}
}