#ifndef UNITTEST_CAMERA_H
#define UNITTEST_CAMERA_H

#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include "GLM/include/glm/gtc/matrix_transform.hpp"
#include "SceneManager/Camera/Camera.h"

namespace Atum
{
	namespace UnitTest
	{
		class CameraUnitTests : public testing::Test
		{
		protected:

			CameraUnitTests()
			: m_position(1,1,1)
			, m_POI(0,0,0)
			, m_upVector(-1,1,-1)
			, m_camera1(m_position, m_POI, m_upVector)
			{
			}

			virtual ~CameraUnitTests()
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}

			glm::vec3 m_position; 
			glm::vec3 m_POI; 
			glm::vec3 m_upVector;
			SceneManager::Camera m_camera1;
		};

		// Tests constructor and getters
		TEST_F(CameraUnitTests, CreateCamera)
		{
			EXPECT_EQ(glm::vec3(1,1,1), m_camera1.GetPosition());
			EXPECT_EQ(glm::vec3(0,0,0), m_camera1.GetPOI());
			EXPECT_EQ(glm::vec3(-1,1,-1), m_camera1.GetUp());

			glm::vec3 newPosition(10,10,10);
			glm::vec3 newPOI(0,10,0);
			glm::vec3 newUp(0,10,0);

			m_camera1.SetViewMatrix(newPosition, newPOI, newUp);
			EXPECT_EQ(newPosition, m_camera1.GetPosition());
			EXPECT_EQ(newPOI, m_camera1.GetPOI());
			EXPECT_EQ(newUp, m_camera1.GetUp());
		}

		// Test calculation of lookat
		TEST_F(CameraUnitTests, GetLookAt)
		{
			// If we are at (1,1,1) and looking at (0,0,0) than the LookAt is (-1,-1,-1)
			EXPECT_EQ(glm::normalize(glm::vec3(-1,-1,-1)), m_camera1.GetLookAt());

			glm::vec3 newPosition(10,10,10);
			glm::vec3 newPOI(0,10,0);
			glm::vec3 newUp(0,10,0);

			m_camera1.SetViewMatrix(newPosition, newPOI, newUp);
			glm::vec3 actualLookAt = m_camera1.GetLookAt();
			glm::vec3 expectedLookAt = glm::normalize(glm::vec3(-1,0,-1));

			// Because of numerical imprecisions
			EXPECT_FLOAT_EQ(expectedLookAt.x, actualLookAt.x);
			EXPECT_FLOAT_EQ(expectedLookAt.y, actualLookAt.y);
			EXPECT_FLOAT_EQ(expectedLookAt.z, actualLookAt.z);
		}

		TEST_F(CameraUnitTests, GetViewMatrix)
		{
			glm::mat4x4 lookAtMatrix(glm::lookAt(m_position, m_POI, m_upVector));
			EXPECT_EQ(lookAtMatrix, m_camera1.GetViewMatrix());
		}
	}
}

#endif
