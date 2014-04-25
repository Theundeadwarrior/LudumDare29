#ifndef SCENEMANAGER_OBJECT_CPP
#define SCENEMANAGER_OBJECT_CPP

#include "SkyBox.h"

#include "Utilities/IdGenerator/IdGenerator.h"

#include "SceneManager/SceneManager.h"
#include "SceneManager/Manager/MaterialManager.h"
#include "SceneManager/Manager/GeometryManager.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Properties/PropertyList.h"
#include "SceneManager/Properties/Property.h"
#include "Events/EventManager.h"
#include "GLM/include/glm/gtc/matrix_transform.hpp"
#include <LowLevelGraphics/Material/Texture/TextureSkyBox.h>
#include <LowLevelGraphics/Material/Texture/Texture.h>
#include "LowLevelGraphics/Material/Shader/ShaderProgram.h"

namespace Atum
{
namespace SceneManager
{
	SkyBox::SkyBox( MaterialID materialID, GeometryID geometryID) : m_materialID(materialID), m_geometryID(geometryID)
	{
	}

	SkyBox::~SkyBox()
	{}

	Material* const SkyBox::GetMaterial()
	{
		return SceneManager::GetInstance().GetMaterialManager()->GetMaterial(m_materialID);
	}


	const LowLevelGraphics::Geometry* const SkyBox::GetGeometry()
	{
		return SceneManager::GetInstance().GetGeometryManager()->GetGeometry(m_geometryID);
	}

	void SkyBox::UpdateViewMatrix(glm::mat4 & viewMatrix)
	{
		glm::vec3 tempPosition;
		tempPosition.x = viewMatrix[3][0];
		tempPosition.y = viewMatrix[3][1];
		tempPosition.z = viewMatrix[3][2];

		// Model View Matrix (model is identity)
		// We only want the orientation information of the view matrix
		viewMatrix[3][0] = viewMatrix[3][1] = viewMatrix[3][2] = 0.0f;
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameter(LowLevelGraphics::MODELVIEWMATRIX, &viewMatrix[0][0], SHADER_MATRIX44);
		viewMatrix[3][0] = tempPosition.x;
		viewMatrix[3][1] = tempPosition.y;
		viewMatrix[3][2] = tempPosition.z;
	}

	void SkyBox::UpdateProjectionMatrix()
	{
		glm::mat4x4 perspective = glm::perspective(45.0f,1024/768.0f, 0.1f, 6000.0f);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("ProjectionMatrixSkyBox", &perspective[0][0], SHADER_MATRIX44);
	}

	void SkyBox::UpdateTextureSkyBox()
	{
		GetMaterial()->BindShaderParameters();
	}

} // namespace SceneManager
} // namespace Atum


#endif
