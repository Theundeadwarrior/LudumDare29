#ifndef SCENEMANAGER_LEVEL_H
#define SCENEMANAGER_LEVEL_H

#include <vector>

#define INVALID_UNSIGNED_INT (unsigned int)-1
#define JUMP_LEVEL_ID -1

namespace Atum
{
namespace SceneManager
{
	class LevelLayout
	{
	public:
		LevelLayout(unsigned int width = 0);
		~LevelLayout() {};

		void Update();
		unsigned int GetLength() const { return m_height.size(); }
		
		std::vector<int> m_height;
		std::vector<unsigned int> m_specialTiles;

	};

	class LevelLayoutGenerator
	{
	public:
		struct Parameters
		{
			Parameters(){}
			
			unsigned int LevelWidth;
			unsigned int LevelHeight;

			unsigned int PlatformLenghtRange[2];

			// unsigned int FallingObjectsProbabilityRange[2];
			// unsigned int ObjectFromTheGroundProbabilityRange[2];
			// unsigned int ProbabilityOfGoingUpRange[2];

			// bool IsUnderGround;
		};
	
	public:
		LevelLayoutGenerator();
		~LevelLayoutGenerator();

		LevelLayout GenerateLevel(const Parameters& params, unsigned int currentHeight = INVALID_UNSIGNED_INT);

		int GetNextJumpLength(int jumpHeight);
		int GetNextJumpHeight(unsigned int currentHeight, const Parameters &params);


	private:

		void AddJump(LevelLayout& level, unsigned int lenght);
		void AddPlatform(LevelLayout& level, unsigned int height, unsigned int width);
	
	};
} // namespace SceneManager
} // namespace Atum


#endif // SCENEMANAGER_LEVEL_H
