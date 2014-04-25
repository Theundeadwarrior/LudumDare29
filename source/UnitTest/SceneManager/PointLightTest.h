#ifndef UNITTEST_POINTLIGHT_H
#define UNITTEST_POINTLIGHT_H

#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 



#include "SceneManager/Lights/PointLight.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Utilities/Transform.h"




namespace Atum
{
	namespace UnitTest
	{
		class PointLightUnitTests : public testing::Test
		{
		protected:

			PointLightUnitTests()
			{

			}

			virtual ~PointLightUnitTests()
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}
		};

		// We're using the manager to create a default material (we just need a shaderId)
		TEST_F(PointLightUnitTests, DefaultConstructor)
		{
			SceneManager::PointLight light;
			SceneManager::LightBaseParams referenceParam;
			SceneManager::Transform tref;

			EXPECT_EQ(light.GetAmbient(), referenceParam.ambient);
			EXPECT_EQ(light.GetSpecular(), referenceParam.specular);
			EXPECT_EQ(light.GetDiffuse(), referenceParam.diffuse);
			EXPECT_FLOAT_EQ(light.GetRadius(),5.0f);

			EXPECT_EQ(light.GetTransform()->GetMatrix(), tref.GetMatrix());
		}

		// Tests constructor
		TEST_F(PointLightUnitTests, Constructor)
		{
			SceneManager::LightBaseParams param(glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(0.5f,0.5f,0.5f,0.5f));
			SceneManager::Transform transform;
			float radius = 4.0f;

			SceneManager::PointLight light(param, transform, radius);
			
			EXPECT_EQ(light.GetAmbient(), param.ambient);
			EXPECT_EQ(light.GetSpecular(), param.specular);
			EXPECT_EQ(light.GetDiffuse(), param.diffuse);
			EXPECT_FLOAT_EQ(light.GetRadius(),radius);

			EXPECT_EQ(light.GetTransform()->GetMatrix(), transform.GetMatrix());
		}

		// Setters
		TEST_F(PointLightUnitTests, SettingParameter)
		{
			glm::vec4 ambient(0.3f,0.3f,0.3f,0.3f);
			glm::vec4 diffuse(0.5f,0.5f,0.5f,0.5f);
			glm::vec4 specular(0.7f,0.7f,0.7f,0.7f);
			float radius = 10;
			int index = 4;
			
			glm::vec3 xAxis(1,0,0); glm::vec3 yAxis(0,1,0); glm::vec3 zAxis(0,0,1);
			glm::vec3 scale(1,1,1); glm::vec3 position(0,0,0);
			SceneManager::Transform transform(position, xAxis, yAxis, zAxis, scale);

			SceneManager::PointLight light;
			light.SetAmbient(ambient);
			light.SetDiffuse(diffuse);
			light.SetSpecular(specular);
			light.SetRadius(radius);
			light.SetTransform(transform);
			light.SetIndex(index);

			EXPECT_EQ(light.GetAmbient(), ambient);
			EXPECT_EQ(light.GetSpecular(), specular);
			EXPECT_EQ(light.GetDiffuse(), diffuse);
			EXPECT_FLOAT_EQ(light.GetRadius(),radius);
			EXPECT_EQ(light.GetIndex(), index);

			EXPECT_EQ(light.GetTransform()->GetMatrix(), transform.GetMatrix());
		}
	
	}
}

#endif
