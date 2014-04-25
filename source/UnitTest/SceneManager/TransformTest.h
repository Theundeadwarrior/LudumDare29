#ifndef UNITTEST_TRANSFORM_H
#define UNITTEST_TRANSFORM_H

#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include "SceneManager/Utilities/Transform.h"

namespace Atum
{
	namespace UnitTest
	{
		class TransformUnitTests : public testing::Test
		{
		protected:

			TransformUnitTests()
			{
				m_transform = SceneManager::Transform();
			}

			virtual ~TransformUnitTests()
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}

			SceneManager::Transform m_transform;
			glm::mat4x4 m_identity;
		};

		// Tests the default constructor
		TEST_F(TransformUnitTests, CreateTransformDefaultReturnsIdentity)
		{
			SceneManager::Transform transform;
			glm::mat4x4 transformMatrix;
			transform.GetMatrix(transformMatrix);

			EXPECT_EQ(m_identity, transformMatrix);
		}

		// Test constructor with axis
		TEST_F(TransformUnitTests, CreateTransformFromAxis)
		{
			// we want an identity matrix here
			glm::vec3 xAxis(1,0,0); glm::vec3 yAxis(0,1,0); glm::vec3 zAxis(0,0,1);
			glm::vec3 scale(1,1,1); glm::vec3 position(0,0,0);
			SceneManager::Transform transform(position, xAxis, yAxis, zAxis, scale);
			EXPECT_EQ(m_identity, transform.GetMatrix());

			// we want to have a matrix where x points towards +y and y points towards -x
			xAxis = glm::vec3(0,1,0); yAxis = glm::vec3(-1,0,0);
			transform = SceneManager::Transform(position, xAxis, yAxis, zAxis, scale);
			glm::mat4x4 expectedMatrix(0,1,0,0,-1,0,0,0,0,0,1,0,0,0,0,1);
			EXPECT_EQ(expectedMatrix, transform.GetMatrix());

			// we want y axis facing -z and z axis going +y
			xAxis = glm::vec3(1,0,0); yAxis = glm::vec3(0,0,-1); zAxis = glm::vec3(0,1,0);
			transform = SceneManager::Transform(position, xAxis, yAxis, zAxis, scale);
			expectedMatrix = glm::mat4x4(1,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,1);
			EXPECT_EQ(expectedMatrix, transform.GetMatrix());			
		}

		// Tests the constructor with rotationMatrix
		TEST_F(TransformUnitTests, CreateTransformFromRotationMatrix)
		{
			// No rotation, position (1,1,1) and uniform scale of 2
			glm::vec3 position(1,1,1);
			glm::mat4x4 rotationMatrix(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
			glm::vec3 scale(2,2,2);
			SceneManager::Transform transform(position, rotationMatrix, scale);
			glm::mat4x4 expectedMatrix(2,0,0,0,0,2,0,0,0,0,2,0,1,1,1,1);
			EXPECT_EQ(expectedMatrix, transform.GetMatrix());	
		}

		// Tests translations
		TEST_F(TransformUnitTests, SetTranslateAndTranslate)
		{
			// SetTranslate
			m_transform.SetTranslate(glm::vec3(4,100,-0.005));
			glm::mat4x4 expectedMatrix(1,0,0,0,0,1,0,0,0,0,1,0,4,100,-0.005,1);
			m_transform.UpdateMatrices();
			EXPECT_EQ(expectedMatrix, m_transform.GetMatrix());

			// Translate back to identity
			m_transform.Translate(glm::vec3(-4,-100,0.005));
			m_transform.UpdateMatrices();
			EXPECT_EQ(m_identity, m_transform.GetMatrix());
		}

		// Tests scaling
		TEST_F(TransformUnitTests, SetScaleAndScale)
		{
			// Set Scale
			m_transform.SetScale(glm::vec3(-1,10,0.005f));
			glm::mat4x4 expectedMatrix(-1,0,0,0,0,10,0,0,0,0,0.005f,0,0,0,0,1);
			m_transform.UpdateMatrices();
			EXPECT_EQ(expectedMatrix, m_transform.GetMatrix());

			// Scale back to identity
			m_transform.Scale(glm::vec3(-1, 0.1f, 200));
			m_transform.UpdateMatrices();
			EXPECT_EQ(m_identity, m_transform.GetMatrix());
		}

		// Tests GetInverseMatrix
		TEST_F(TransformUnitTests, GetInverseMatrix)
		{
			// We know that the inverse of identity is identity
			EXPECT_EQ(m_identity, m_transform.GetInverseMatrix());

			glm::mat4x4 inverseMatrix;
			m_transform.GetInverseMatrix(inverseMatrix);
			EXPECT_EQ(m_identity, inverseMatrix);

		}
	}
}

#endif
