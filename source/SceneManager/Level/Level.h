#ifndef SCENEMANAGER_LEVEL_H
#define SCENEMANAGER_LEVEL_H

#include <vector>

#define INVALID_UNSIGNED_INT (unsigned int)-1
#define JUMP_LEVEL_ID -1
#define SPECIAL_TILE_BRIDGE 4

namespace Atum
{
namespace SceneManager
{

	struct PlatformInfo
	{

		enum PlatformType
		{
			E_Jump,
			E_Canyon,
			E_Ruins,
			E_Bridge
		};

		PlatformInfo(PlatformType type, unsigned int height, unsigned int length) : Type(type), Height(height), Length(length) {}

		PlatformType Type;
		unsigned int Length;
		unsigned int Height;
	};

	class LevelLayout
	{
	public:
		LevelLayout(unsigned int width = 0);
		~LevelLayout() {};

		void Update();

		std::vector<PlatformInfo> m_platforms;
	};

	class LevelLayoutGenerator
	{
	public:
		struct Parameters
		{
			Parameters();
			
			unsigned int LevelWidth;
			unsigned int LevelHeight;

			unsigned int PlatformLenghtRange[2];

			float BridgeProbability;
			// unsigned int FallingObjectsProbabilityRange[2];
			// unsigned int ObjectFromTheGroundProbabilityRange[2];
			// unsigned int ProbabilityOfGoingUpRange[2];

			bool IsUnderGround;
		};
	
	public:
		LevelLayoutGenerator(const Parameters& params);
		~LevelLayoutGenerator();

		LevelLayout GenerateLevel(unsigned int currentHeight = INVALID_UNSIGNED_INT);

		int GetNextJumpLength(int jumpHeight);
		int GetNextJumpHeight(unsigned int currentHeight, const Parameters &params);


	private:
		void AddJump(LevelLayout& level, unsigned int lenght);
		void AddPlatform(LevelLayout& level, unsigned int height, unsigned int width);
		void GenerateBridge(LevelLayout& level);

		// new system
		void CreateBridge(LevelLayout& level, unsigned int indexOfPlatform);

	private:
		Parameters m_params;
	};
} // namespace SceneManager
} // namespace Atum


#endif // SCENEMANAGER_LEVEL_H
