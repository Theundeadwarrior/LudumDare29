#ifndef UNITTEST_PHYSICSENGINE_H
#define UNITTEST_PHYSICSENGINE_H

#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include <PhysicsEngine/PhysicsEngine.h>
#include <PhysicsEngine/Objects/PhysicsObject.h>
#include <Utilities/BasicGeometry/BasicGeometryGenerator.h>

namespace Atum
{
	namespace UnitTest
	{
		class PhysicsEngineUnitTests : public testing::Test
		{
		protected:

			PhysicsEngineUnitTests()
			{
				m_convexMeshCube.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
				m_convexMeshCube.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
				m_convexMeshCube.push_back(glm::vec3(1.0f,1.0f,-1.0f));
				m_convexMeshCube.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
				m_convexMeshCube.push_back(glm::vec3(-1.0f,-1.0f,1.0f));
				m_convexMeshCube.push_back(glm::vec3(-1.0f,1.0f,1.0f));
				m_convexMeshCube.push_back(glm::vec3(1.0f,1.0f,1.0f));
				m_convexMeshCube.push_back(glm::vec3(1.0f,-1.0f,1.0f));
			}

			virtual ~PhysicsEngineUnitTests()
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}

			vector<glm::vec3> m_convexMeshCube;
		};

		// Instanciating the physics engine, this test is successful if there is no exception
		TEST_F(PhysicsEngineUnitTests, ConstructorTest)
		{
			PhysicsEngine::PhysicsEngine& physicsEngine = PhysicsEngine::PhysicsEngine::GetInstance();
		}

		// Create an invalid static object in the physics scene (the number of vertices exceed 256)
		TEST_F(PhysicsEngineUnitTests, CreateInvalidStaticSphereObject)
		{
			PhysicsEngine::PhysicsEngine& physicsEngine = PhysicsEngine::PhysicsEngine::GetInstance();
			LowLevelGraphics::GeometryParameters geometryParameters;
			geometryParameters = Utilities::CreateSphereGeometry(1.0f, 17, 17);

			EXPECT_EQ(geometryParameters.position.size(), 470); // we exceed 256 vertices
			PhysicsEngine::PhysicsObject* physicsObject = physicsEngine.GetScene()->AddStaticObject(&geometryParameters.position[0], geometryParameters.position.size(), physx::PxVec3(0.0f,2.0f,0.0f), 0.7f, 0.6f, 0.3f);
			physicsEngine.GetScene()->CreatePlane();
			EXPECT_FALSE(physicsObject); // the object is expected to be null

			std::vector<PhysicsEngine::PhysicsObject*>::iterator itBegin = physicsEngine.GetScene()->GetBeginPhysicsObjectList();
			std::vector<PhysicsEngine::PhysicsObject*>::iterator itEnd = physicsEngine.GetScene()->GetEndPhysicsObjectList();

			// If the object is successfully created, it will be added to the list
			EXPECT_TRUE(itBegin==itEnd);
		}

		// Create a static object in the physics scene
		TEST_F(PhysicsEngineUnitTests, CreateStaticCubeObject)
		{
			PhysicsEngine::PhysicsEngine& physicsEngine = PhysicsEngine::PhysicsEngine::GetInstance();
			PhysicsEngine::PhysicsObject* physicsObject = physicsEngine.GetScene()->AddStaticObject(&m_convexMeshCube[0], m_convexMeshCube.size(), physx::PxVec3(0.0f,2.0f,0.0f), 0.7f, 0.6f, 0.3f);
			physicsEngine.GetScene()->CreatePlane();
			EXPECT_TRUE(physicsObject);

			std::vector<PhysicsEngine::PhysicsObject*>::iterator itBegin = physicsEngine.GetScene()->GetBeginPhysicsObjectList();
			std::vector<PhysicsEngine::PhysicsObject*>::iterator itEnd = physicsEngine.GetScene()->GetEndPhysicsObjectList();

			// If the object is successfully created, it will be added to the list
			EXPECT_TRUE(itBegin!=itEnd);
			EXPECT_TRUE(*itBegin);
		}

		// Create a dynamic object in the physics scene
		TEST_F(PhysicsEngineUnitTests, CreateDynamicCubeObject)
		{
			PhysicsEngine::PhysicsEngine& physicsEngine = PhysicsEngine::PhysicsEngine::GetInstance();
			PhysicsEngine::PhysicsObject* physicsObject = physicsEngine.GetScene()->AddDynamicObject(&m_convexMeshCube[0], m_convexMeshCube.size(), physx::PxVec3(0.0f,2.0f,0.0f), 0.7f, 0.6f, 0.3f);
			physicsEngine.GetScene()->CreatePlane();
			EXPECT_TRUE(physicsObject);

			std::vector<PhysicsEngine::PhysicsObject*>::iterator itBegin = physicsEngine.GetScene()->GetBeginPhysicsObjectList();
			std::vector<PhysicsEngine::PhysicsObject*>::iterator itEnd = physicsEngine.GetScene()->GetEndPhysicsObjectList();
			itBegin++; // the first object is the static cube from the first unit test
			EXPECT_TRUE(itBegin!=itEnd);
			EXPECT_TRUE(*itBegin);
		}
	}
}

#endif
