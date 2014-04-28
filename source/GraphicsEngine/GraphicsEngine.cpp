#include "GraphicsEngine/GraphicsEngine.h"

#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include "LowLevelGraphics/Material/Texture/Texture.h"
#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Camera/PerspectiveCamera.h"
#include "SceneManager/SceneManager.h"

#include "UserInterface/Ui/UiManager.h"

#include "SceneManager/Objects/GameplayObjects/Background.h"
#include "SceneManager/Objects/GameplayObjects/ForeGround.h"
#include "SceneManager/Objects/GameplayObjects/MovingBackground.h"

namespace Atum
{

namespace GraphicsEngine
{

//-----------------------------------------------------------------------------
GraphicsEngine::GraphicsEngine(int argc, char *argv[])
{
    LowLevelGraphics::LowLevelAPI::Initialize(&argc, argv);

    LowLevelGraphics::WindowParameters params("Graphic Engine", 1280, 720, 0, 0);
    LowLevelGraphics::WindowManager::GetInstance().AddWindow(params);
}

//-----------------------------------------------------------------------------
GraphicsEngine::~GraphicsEngine()
{

}

//-----------------------------------------------------------------------------
void GraphicsEngine::StartRendering(SceneManager::Scene* scene)
{
    LowLevelGraphics::LowLevelAPI::BeginFrame();

    Preprocess();
    //Todo : use render units and update local shader params
    Render(scene); 
}

void GraphicsEngine::Preprocess()
{
    //Todo : set shader params here (lighting, etc.), half of all the cool stuff, the other half being in shaders ;)
}

//-----------------------------------------------------------------------------
void GraphicsEngine::Render(SceneManager::Scene* scene)
{
	   LowLevelGraphics::LowLevelAPI::EnableDepthRead();
	   {
			LowLevelGraphics::LowLevelAPI::EnableBackFaceCulling();
			{
				LowLevelGraphics::LowLevelAPI::EnableDepthWrite();
				DrawOpaqueObjects(scene);
				LowLevelGraphics::LowLevelAPI::DisableDepthWrite();

				LowLevelGraphics::LowLevelAPI::EnableAlphaBlending();
				{
					LowLevelGraphics::LowLevelAPI::SetAlphaBlendFunc();
					DrawAlphaObjects(scene);
				}
				LowLevelGraphics::LowLevelAPI::DisableDepthRead();

				LowLevelGraphics::LowLevelAPI::UnlockShaderPointSize();
				LowLevelGraphics::LowLevelAPI::SetAdditiveBlendFunc();
				DrawParticles(scene);
				LowLevelGraphics::LowLevelAPI::LockShaderPointSize();

				LowLevelGraphics::LowLevelAPI::DisableAlphaBlending();
			}
			LowLevelGraphics::LowLevelAPI::DisableBackFaceCulling();
	   }
	   LowLevelGraphics::LowLevelAPI::DisableDepthRead();
}

//-----------------------------------------------------------------------------
void GraphicsEngine::StopRendering()
{
	if(m_photographer.IsScreenShotRequested())
	{
		m_photographer.TakeScreenShot();
	}

	UserInterface::UiManager::GetInstance().DrawPanels();
    LowLevelGraphics::LowLevelAPI::EndFrame();
}

//-----------------------------------------------------------------------------
void GraphicsEngine::DrawAlphaObjects(SceneManager::Scene* scene)
{
	std::list<SceneManager::Object*>::iterator it = scene->GetBeginObjectList();
	std::list<SceneManager::Object*>::iterator itEnd = scene->GetEndObjectList();

	SceneManager::Camera* const cam = scene->GetCurrentCamera();
	glm::mat4x4 viewMatrix = cam->GetViewMatrix();

	for(;it!=itEnd;++it)
	{
		if(dynamic_cast<SceneManager::MovingBackground*>(*it))
		{
			// We use the corresponding shader
			LowLevelGraphics::LowLevelAPI::BindShaders((*it)->GetMaterial()->GetShaderList());

			LowLevelGraphics::ShaderProgram* shaderProgram = (*it)->GetMaterial()->GetShaderList()->GetShaderProgram();

			// Here, we send the global parameters to the shader
			glm::mat4x4 modelMatrix;
			(*it)->GetTransform()->GetMatrix(modelMatrix);
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::MODELMATRIX, &modelMatrix[0][0], SHADER_MATRIX44);
			glm::mat4x4 modelViewMatrix =  viewMatrix * modelMatrix;
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::MODELVIEWMATRIX, &modelViewMatrix[0][0], SHADER_MATRIX44);
			glm::mat3x3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelViewMatrix)));
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::NORMALMATRIX, &normalMatrix[0][0], SHADER_MATRIX33);

			// We send the local parameters of the material to the shader
			(*it)->BindShaderParameters();

			// We render
			LowLevelGraphics::LowLevelAPI::DrawCall((*it)->GetGeometry(),shaderProgram->GetProgramId());

			(*it)->GetMaterial()->UnbindShaderParameters();
			LowLevelGraphics::LowLevelAPI::UnbindShaders();
		}
	}
}

//-----------------------------------------------------------------------------
void GraphicsEngine::DrawOpaqueObjects(SceneManager::Scene* scene)
{
    std::list<SceneManager::Object*>::iterator it = scene->GetBeginObjectList();
    std::list<SceneManager::Object*>::iterator itEnd = scene->GetEndObjectList();

    SceneManager::Camera* const cam = scene->GetCurrentCamera();
    glm::mat4x4 viewMatrix = cam->GetViewMatrix();

    for(;it!=itEnd;++it)
    {
		if(!dynamic_cast<SceneManager::MovingBackground*>(*it))
		{
			// We use the corresponding shader
			LowLevelGraphics::LowLevelAPI::BindShaders((*it)->GetMaterial()->GetShaderList());

			LowLevelGraphics::ShaderProgram* shaderProgram = (*it)->GetMaterial()->GetShaderList()->GetShaderProgram();

			// Here, we send the global parameters to the shader
			glm::mat4x4 modelMatrix;
			(*it)->GetTransform()->GetMatrix(modelMatrix);
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::MODELMATRIX, &modelMatrix[0][0], SHADER_MATRIX44);
			glm::mat4x4 modelViewMatrix =  viewMatrix * modelMatrix;
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::MODELVIEWMATRIX, &modelViewMatrix[0][0], SHADER_MATRIX44);
			glm::mat3x3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelViewMatrix)));
			shaderProgram->UpdateShaderParameter(LowLevelGraphics::NORMALMATRIX, &normalMatrix[0][0], SHADER_MATRIX33);

			// We send the local parameters of the material to the shader
			(*it)->BindShaderParameters();

			// We render
			LowLevelGraphics::LowLevelAPI::DrawCall((*it)->GetGeometry(),shaderProgram->GetProgramId());

			(*it)->GetMaterial()->UnbindShaderParameters();
			LowLevelGraphics::LowLevelAPI::UnbindShaders();
		}
    }
}

//-----------------------------------------------------------------------------
void GraphicsEngine::DrawParticles(SceneManager::Scene* scene)
{
	std::vector<ParticleSystem::ParticleSystem*>::iterator psIt = scene->GetBeginParticleSystemList();
	std::vector<ParticleSystem::ParticleSystem*>::iterator psItEnd = scene->GetEndParticleSystemList();

	for(;psIt != psItEnd; ++psIt)
	{
		(*psIt)->Draw();		
	}
}



void GraphicsEngine::DrawPointLightSphere( SceneManager::Scene* scene )
{
	const UserInterface::UiManager& manager = UserInterface::UiManager::GetInstance();
	SceneManager::PerspectiveCamera* camera ( 
		dynamic_cast<SceneManager::PerspectiveCamera*>(scene->GetCurrentCamera()) );
	
	if ( manager.IsLightSelectionModeEnabled() && camera )
	{
		std::vector<SceneManager::PointLight*>::iterator lightIter = 
			SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetBeginPointLightList();
		std::vector<SceneManager::PointLight*>::iterator lightIterEnd =
			SceneManager::SceneManager::GetInstance().GetCurrentScene()->GetEndPointLightList();

		for ( ; lightIter != lightIterEnd; lightIter++ )
		{
			glm::mat4x4 viewMatrix;
			camera->GetViewMatrix(viewMatrix);

			glm::mat4x4 modelViewMatrix( viewMatrix * (*lightIter)->GetTransform()->GetMatrix() );

			glm::mat4x4 perspectiveMatrix;
			camera->GetPerspectiveMat(perspectiveMatrix);

			LowLevelGraphics::LowLevelAPI::DrawSphere(&modelViewMatrix[0][0], &perspectiveMatrix[0][0]);
		}
	}
}

}
}
