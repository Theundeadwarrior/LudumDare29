#ifndef UNITTEST_OBJECTLOADERUNITTESTS_H
#define UNITTEST_OBJECTLOADERUNITTESTS_H
#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include <Utilities/Loader/ObjectLoader.h>

namespace Atum
{
	namespace UnitTest
	{
		struct DataTestsObjectLoader
		{
			bool isSuccess;
			const char * objectFile;
			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			vector<glm::vec2> uvs;
			unsigned int expectedVerticesSize;
			unsigned int expectedNormalsSize;
			unsigned int expectedUvsSize;
		};

		class ObjectLoaderUnitTests : public testing::Test {
		
		protected:
			DataTestsObjectLoader m_dataTestsObjectLoader;

			ObjectLoaderUnitTests()
			{
				// Create data for the plane object (2 triangles, 6 vertices, 6 normals and 6 uvs)
				m_dataTestsObjectLoader.isSuccess = true;
				m_dataTestsObjectLoader.expectedVerticesSize = 6;
				m_dataTestsObjectLoader.expectedNormalsSize = 6;
				m_dataTestsObjectLoader.expectedUvsSize = 6;
				m_dataTestsObjectLoader.objectFile = "../../data/models/plane.obj";
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(1.0f,0.0f,-1.0f));
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(-1.0f,0.0f,-1.0f));
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(-1.0f,0.0f,1.0f));
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(1.0f,0.0f,1.0f));
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(1.0f,0.0f,-1.0f));
				m_dataTestsObjectLoader.vertices.push_back(glm::vec3(-1.0f,0.0f,1.0f));

				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));
				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));
				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));
				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));
				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));
				m_dataTestsObjectLoader.normals.push_back(glm::vec3(0,1,0));

				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(1.0f,1.0f));
				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(0.0f,1.0f));
				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(0.0f,0.0f));
				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(1.0f,0.0f));
				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(1.0f,1.0f));
				m_dataTestsObjectLoader.uvs.push_back(glm::vec2(0.0f,0.0f));
			}

			virtual ~ObjectLoaderUnitTests()
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

		// Test the success of functions of the object loader utility
		TEST_F(ObjectLoaderUnitTests, TestLoadBasicPlane)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, m_dataTestsObjectLoader.objectFile, "r") == 0);

			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			vector<glm::vec2> uvs;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ(m_dataTestsObjectLoader.objectFile, vertices, normals, uvs);
			EXPECT_EQ(m_dataTestsObjectLoader.isSuccess, isLoaded);

			EXPECT_EQ(m_dataTestsObjectLoader.expectedVerticesSize, vertices.size());
			EXPECT_EQ(m_dataTestsObjectLoader.expectedNormalsSize, normals.size());
			EXPECT_EQ(m_dataTestsObjectLoader.expectedUvsSize, uvs.size());

			EXPECT_EQ(m_dataTestsObjectLoader.vertices, vertices);
			EXPECT_EQ(m_dataTestsObjectLoader.normals, normals);
			EXPECT_EQ(m_dataTestsObjectLoader.uvs, uvs);
		}

		TEST_F(ObjectLoaderUnitTests, TestLoadBunny)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/Bunny.obj", "r") == 0);
			vector<glm::vec3> vertices;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/Bunny.obj", vertices);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(vertices.size(), 208992);
		}

		TEST_F(ObjectLoaderUnitTests, TestLoadBunnyUV)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/BunnyUV.obj", "r") == 0);
			vector<glm::vec3> vertices;
			vector<glm::vec2> uvs;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/BunnyUV.obj", vertices, uvs);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(vertices.size(), 208992);
			EXPECT_EQ(vertices.size(), uvs.size());
		}
		
		TEST_F(ObjectLoaderUnitTests, TestLoadTable)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/table.obj", "r") == 0);
			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			// The table object has no uvs info in the obj file
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/table.obj", vertices, normals);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(vertices.size(), 107106);
			EXPECT_EQ(vertices.size(),normals.size());
		}

		TEST_F(ObjectLoaderUnitTests, TestLoadTablePhysics)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/tablePhysic.obj", "r") == 0);
			vector<glm::vec3> convexVertices;
			bool isLoaded = Utilities::ObjectLoader::LoadPhysicMeshOBJ("../../data/models/tablePhysic.obj", convexVertices);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(convexVertices.size(), 26);
		}

		TEST_F(ObjectLoaderUnitTests, TestLoadCube)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/cube.obj", "r") == 0);
			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/cube.obj", vertices, normals);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(vertices.size(), 36);
			EXPECT_EQ(vertices.size(), normals.size());
		}

		TEST_F(ObjectLoaderUnitTests, TestLoadChalice)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/chalice.obj", "r") == 0);
			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			vector<glm::vec2> uvs;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/chalice.obj", vertices, normals, uvs);
			EXPECT_TRUE(isLoaded);
			EXPECT_EQ(vertices.size(), 1584);
			EXPECT_EQ(vertices.size(), normals.size());
			EXPECT_EQ(normals.size(), uvs.size());
		}

		// Test the failure of the functions of the object loader utility
		// Try to open a file that doesn't exist on disk
		TEST_F(ObjectLoaderUnitTests, TestLoadFileFailure)
		{
			FILE * objectFile;
			EXPECT_FALSE(fopen_s(&objectFile, "../../data/models/noFile.obj", "r") == 0);

			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/noFile.obj", vertices, normals);
			EXPECT_FALSE(isLoaded);
		}

		// Try to get the uv info when it is not in the object file
		TEST_F(ObjectLoaderUnitTests, TestLoadCubeFailure)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/cube.obj", "r") == 0);
			vector<glm::vec3> vertices;
			vector<glm::vec3> normals;
			vector<glm::vec2> uvs;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/cube.obj", vertices, normals, uvs);
			EXPECT_FALSE(isLoaded);
		}

		// Try to get only the vertices info when there are the vertices, normals and uvs
		TEST_F(ObjectLoaderUnitTests, TestLoadChaliceFailure)
		{
			FILE * objectFile;
			EXPECT_TRUE(fopen_s(&objectFile, "../../data/models/chalice.obj", "r") == 0);
			vector<glm::vec3> vertices;
			bool isLoaded = Utilities::ObjectLoader::LoadVisualMeshOBJ("../../data/models/chalice.obj", vertices);
			EXPECT_FALSE(isLoaded);
		}
	}
}

#endif