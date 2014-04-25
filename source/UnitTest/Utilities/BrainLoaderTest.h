#ifndef UNITTEST_BRAINLOADERUNITTESTS_H
#define UNITTEST_BRAINLOADERUNITTESTS_H
#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include <LowLevelGraphics/Geometry/Geometry.h>
#include <Utilities/BrainLoader/BrainLoader.h>
#include <Utilities/BrainLoader/Image3D.h>
namespace Atum
{
	namespace UnitTest
	{
		class BrainLoaderUnitTests : public testing::Test {
		protected:
			// You can remove any or all of the following functions if its body
			// is empty.
			vector<string> objects;

			BrainLoaderUnitTests()
			{
				// You can do set-up work for each test here.
			}

			virtual ~BrainLoaderUnitTests()
			{
				// You can do clean-up work that doesn't throw exceptions here.

			}

			// If the constructor and destructor are not enough for setting up
			// and cleaning up each test, you can define the following methods:
			virtual void SetUp()
			{
				// Code here will be called immediately after the constructor (right
				// before each test).
			}

			virtual void TearDown()
			{
				// Code here will be called immediately after each test (right
				// before the destructor).
			}
		};

		TEST_F(BrainLoaderUnitTests, TestLoadBrainGeometry)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/avg152T1_LR_nifti.nii", "r") == 0);
			LowLevelGraphics::GeometryParameters geomParam;
			Utilities::BrainLoader::CreateBrainGeometry("../../data/models/avg152T1_LR_nifti.nii", 5.0f, 5.0f, 5.0f, 1, geomParam);
			EXPECT_EQ(geomParam.position.size(), 459648);
			EXPECT_EQ(geomParam.color.size(), geomParam.position.size());
		}

		TEST_F(BrainLoaderUnitTests, TestLoadNiftiBrain)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/avg152T1_LR_nifti.nii", "r") == 0);
			Utilities::BrainLoader::Image3D brainImage3D;
			bool isLoaded = Utilities::BrainLoader::LoadNiftiBrain("../../data/models/avg152T1_LR_nifti.nii", brainImage3D);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(brainImage3D.GetNbColumns(), 91);
			EXPECT_EQ(brainImage3D.GetNbRows(), 109);
			EXPECT_EQ(brainImage3D.GetNbFrames(), 91);
			EXPECT_EQ(brainImage3D.GetDataSize(), 902629);
		}

		// Test to load invalid nifti path 
		TEST_F(BrainLoaderUnitTests, TestLoadInvalidPathNiftiBrain)
		{
			FILE * objectFile;
			EXPECT_FALSE(fopen_s(&objectFile, "../../data/models/invalidPath.nii", "r") == 0);
			Utilities::BrainLoader::Image3D brainImage3D;
			bool isLoaded = Utilities::BrainLoader::LoadNiftiBrain("../../data/models/invalidPath.nii", brainImage3D);
			EXPECT_FALSE(isLoaded);
		}

		// Load brain geometry with invalid parameters
		TEST_F(BrainLoaderUnitTests, TestLoadBrainGeometryInvalidParameters)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/avg152T1_LR_nifti.nii", "r") == 0);
			LowLevelGraphics::GeometryParameters geomParam;
			Utilities::BrainLoader::CreateBrainGeometry("../../data/models/avg152T1_LR_nifti.nii", -5.0f, -5.0f, -5.0f, -1, geomParam);
			EXPECT_EQ(geomParam.position.size(), 0);
			EXPECT_EQ(geomParam.color.size(), geomParam.position.size());
		}

		TEST_F(BrainLoaderUnitTests, TestGenerateCloudPoints)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/avg152T1_LR_nifti.nii", "r") == 0);
			Utilities::BrainLoader::Image3D brainImage3D;
			bool isLoaded = Utilities::BrainLoader::LoadNiftiBrain("../../data/models/avg152T1_LR_nifti.nii", brainImage3D);
			vector<glm::vec3> vertices;
			vector<glm::vec4> colors;
			Utilities::BrainLoader::GenerateCloudPoints(brainImage3D, 5.0f, 5.0f, 5.0f, 1, vertices, colors);

			EXPECT_EQ(vertices.size(), 459648);
			EXPECT_EQ(colors.size(), 459648);
		}
	}
}

#endif