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
		: BridgeProbability(0.8f)
		, IsUnderGround(false)
	{

	}

	LevelLayout::LevelLayout(unsigned int width)
	{
		m_height.reserve(width);
		m_specialTiles.resize(width, 0);
	}

	void LevelLayout::Dump()
	{
		std::ofstream myfile("../../LevelDump.txt");
		if (myfile.is_open())
		{
			for (int i = 0; i < m_height.size(); ++i)
			{
				myfile << (m_height[i] == -1 ? 'x' : (m_height[i] > 9 ? 'T' : m_height[i]));
			}

			myfile << std::endl;

			for (int i = 0; i < m_height.size(); ++i)
			{
				myfile << m_specialTiles[i];
			}
		}
		myfile.close();
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


		while (level.GetLength() < m_params.LevelWidth)
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
			jumpLength = GenerateRandomNumber(4, 8);
		}
		else if (jumpHeight == 0)
		{
			jumpLength = GenerateRandomNumber(4, 6);
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

	void LevelLayoutGenerator::GenerateBridge(LevelLayout& levelLayout)
	{
		unsigned int currentIndex = 0;
		unsigned int indexOfFirstJumpTile = 0;
		int currentHeight = levelLayout.m_height[currentIndex];
		while (currentIndex < levelLayout.m_height.size())
		{
			currentIndex++;
			while (currentIndex < levelLayout.m_height.size() && currentHeight == levelLayout.m_height[currentIndex])
			{
				currentIndex++;
			}

			indexOfFirstJumpTile = currentIndex;
			while (currentIndex < levelLayout.m_height.size() && levelLayout.m_height[currentIndex] == JUMP_LEVEL_ID)
			{
				currentIndex++;
			}

			if (currentIndex < levelLayout.m_height.size() && levelLayout.m_height[currentIndex] == currentHeight)
			{
				CreateBridge(levelLayout, indexOfFirstJumpTile, currentIndex);
			}
			currentIndex++;

		}
		//throw std::exception("The method or operation is not implemented.");
	}

	void LevelLayoutGenerator::CreateBridge(LevelLayout& levelLayout, unsigned int indexOfFirstJumpTile, unsigned int currentIndex)
	{
		int randomNumber = GenerateRandomNumber(0, 100);

		if (randomNumber < m_params.BridgeProbability * 100)
		{
			for (unsigned int i = indexOfFirstJumpTile; i < currentIndex; ++i)
			{
				levelLayout.m_specialTiles[i] = SPECIAL_TILE_BRIDGE;
			}
		}
		//throw std::exception("The method or operation is not implemented.");
	}

}
}