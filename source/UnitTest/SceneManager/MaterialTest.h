#ifndef UNITTEST_MATERIAL_H
#define UNITTEST_MATERIAL_H

#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 



#include "SceneManager/Material/Material.h"
#include "SceneManager/Manager/MaterialManager.h"
#include "SceneManager/Material/MaterialParameters.h"
#include "SceneManager/SceneManager.h"




namespace Atum
{
	namespace UnitTest
	{
		class MaterialUnitTests : public testing::Test
		{
		protected:

			MaterialUnitTests()
			{

			}

			virtual ~MaterialUnitTests()
			{
			}

			virtual void SetUp()
			{
			}

			virtual void TearDown()
			{
			}

			SceneManager::MaterialManager m_manager;

		};

		// We're using the manager to create a default material (we just need a shaderId)
		TEST_F(MaterialUnitTests, DefaultConstructor)
		{
			SceneManager::ShaderListID dummyShaderListId = 0;

			SceneManager::MaterialID matId = m_manager.CreateMaterial(dummyShaderListId);
			SceneManager::Material* mat = m_manager.GetMaterial(matId);

			EXPECT_EQ(mat->GetMaterialParameters().plainColorParam.m_color, glm::vec4(1,1,1,1));
			EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().diffuseMapParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().phongParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().parallaxParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().skyBoxParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().specularTextureParam.m_isActive);
		}

		// Tests constructor
		TEST_F(MaterialUnitTests, MaterialConstructor)
		{
			SceneManager::ShaderListID dummyShaderListId = 0;
			SceneManager::TextureId dummyTexId = 1;

			SceneManager::MaterialParameters matParam;
			matParam.plainColorParam = SceneManager::PlainColorParameter(glm::vec4(1,1,1,1));
			matParam.diffuseMapParam = SceneManager::TextureParameter(dummyTexId);
			SceneManager::MaterialID matId = m_manager.CreateMaterial(matParam, dummyShaderListId);
			SceneManager::Material* mat = m_manager.GetMaterial(matId);

			EXPECT_EQ(mat->GetMaterialParameters().plainColorParam.m_color, glm::vec4(1,1,1,1));
			EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_EQ(mat->GetMaterialParameters().diffuseMapParam.m_textID, dummyTexId);
			EXPECT_TRUE(mat->GetMaterialParameters().diffuseMapParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().phongParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().parallaxParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().skyBoxParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().specularTextureParam.m_isActive);
		}

		// Test active effect phong on a default material
		TEST_F(MaterialUnitTests, ActivatePhongParam)
		{
			SceneManager::ShaderListID dummyShaderListId = 0;
			SceneManager::MaterialID matId = m_manager.CreateMaterial(dummyShaderListId);
			SceneManager::Material* mat = m_manager.GetMaterial(matId);

			// Activate the effect
			SceneManager::PhongParameter param(glm::vec4(1,1,1,1), glm::vec4(0.5f,0.5f,0.5f,0.5f),glm::vec4(0,0,0,0), 10);
			mat->ActivateEffect(SceneManager::PHONG_SHADING, &param);
			EXPECT_FALSE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_TRUE(mat->GetMaterialParameters().phongParam.m_isActive);
			EXPECT_EQ(mat->GetMaterialParameters().phongParam.m_shininess, param.m_shininess);
			EXPECT_EQ(mat->GetMaterialParameters().phongParam.m_ambiantColor, param.m_ambiantColor);
			EXPECT_EQ(mat->GetMaterialParameters().phongParam.m_diffuseColor, param.m_diffuseColor);
			EXPECT_EQ(mat->GetMaterialParameters().phongParam.m_specularColor, param.m_specularColor);

			// Switch back to no illumination
			SceneManager::PlainColorParameter plainParam(glm::vec4(0.7f,0.7f,0.7f,0.7f));
			mat->ActivateEffect(SceneManager::NO_ILLUMINATION, &plainParam);
			EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_FALSE(mat->GetMaterialParameters().phongParam.m_isActive);
			EXPECT_EQ(mat->GetMaterialParameters().plainColorParam.m_color, plainParam.m_color);
		}

		TEST_F(MaterialUnitTests, ActivateDiffuseMapParam)
		{
			SceneManager::ShaderListID dummyShaderListId = 0;
			SceneManager::MaterialID matId = m_manager.CreateMaterial(dummyShaderListId);
			SceneManager::Material* mat = m_manager.GetMaterial(matId);

			SceneManager::TextureId dummyTexId = 1;
			SceneManager::TextureParameter param(dummyTexId);

			mat->ActivateEffect(SceneManager::DIFFUSE_MAP, &param);
			EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_TRUE(mat->GetMaterialParameters().diffuseMapParam.m_isActive);
			EXPECT_EQ(mat->GetMaterialParameters().diffuseMapParam.m_textID, dummyTexId);

			mat->DeactivateEffect(SceneManager::DIFFUSE_MAP);
			EXPECT_FALSE(mat->GetMaterialParameters().diffuseMapParam.m_isActive);
		}

		// TO ACTIVATE ONCE WE COMPLETE THE SPECULAR MAP IN MATERIAL
		//TEST_F(MaterialUnitTests, ActivateSpecularMapParam)
		//{
		//	SceneManager::ShaderListID dummyShaderListId = 0;
		//	SceneManager::MaterialID matId = m_manager.CreateMaterial(dummyShaderListId);
		//	SceneManager::Material* mat = m_manager.GetMaterial(matId);

		//	SceneManager::TextureId dummyTexId = 1;
		//	SceneManager::TextureParameter param(dummyTexId);

		//	mat->ActivateEffect(SceneManager::SPECULAR_MAP, &param);
		//	EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
		//	EXPECT_TRUE(mat->GetMaterialParameters().specularTextureParam.m_isActive);
		//	EXPECT_EQ(mat->GetMaterialParameters().specularTextureParam.m_textID, dummyTexId);

		//	mat->DeactivateEffect(SceneManager::SPECULAR_MAP);
		//	EXPECT_FALSE(mat->GetMaterialParameters().specularTextureParam.m_isActive);
		//}

		TEST_F(MaterialUnitTests, ActivateParallaxMapParam)
		{
			SceneManager::ShaderListID dummyShaderListId = 0;
			SceneManager::MaterialID matId = m_manager.CreateMaterial(dummyShaderListId);
			SceneManager::Material* mat = m_manager.GetMaterial(matId);

			SceneManager::TextureId dummyTexId = 1;
			SceneManager::ParallaxMapParameters param(dummyTexId, 1.0f, 2.0f);

			mat->ActivateEffect(SceneManager::PARALLAX_MAP, &param);
			EXPECT_TRUE(mat->GetMaterialParameters().plainColorParam.m_isActive);
			EXPECT_TRUE(mat->GetMaterialParameters().parallaxParam.m_isActive);
			EXPECT_EQ(mat->GetMaterialParameters().parallaxParam.m_parallaxmapID, dummyTexId);
			EXPECT_EQ(mat->GetMaterialParameters().parallaxParam.m_parallaxHeightBias, 2.0f);
			EXPECT_EQ(mat->GetMaterialParameters().parallaxParam.m_parallaxHeightScale, 1.0f);

			mat->DeactivateEffect(SceneManager::PARALLAX_MAP);
			EXPECT_FALSE(mat->GetMaterialParameters().parallaxParam.m_isActive);
		}
	}
}

#endif
