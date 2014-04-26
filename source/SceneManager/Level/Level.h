#ifndef SCENEMANAGER_LEVEL_H
#define SCENEMANAGER_LEVEL_H

#include <vector>

#define INVALID_UNSIGNED_INT (unsigned int)-1

namespace Atum
{
namespace SceneManager
{

	class Level
	{
	public:
		Level(unsigned int width = 0);
		~Level() {};

		void Update();
		unsigned int GetLength() const { return m_height.size(); }
		
		std::vector<int> m_height;
		std::vector<unsigned int> m_specialTiles;

	};

	class LevelGenerator
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
		LevelGenerator();
		~LevelGenerator();

		Level GenerateLevel(const Parameters& params, unsigned int currentHeight = INVALID_UNSIGNED_INT);

		int GetNextJumpLength(int jumpHeight);
		int GetNextJumpHeight(unsigned int currentHeight, const Parameters &params);


	private:

		void AddJump(Level& level, unsigned int lenght);
		void AddPlatform(Level& level, unsigned int height, unsigned int width);
	
	};
} // namespace SceneManager
} // namespace Atum


#endif // SCENEMANAGER_LEVEL_H
