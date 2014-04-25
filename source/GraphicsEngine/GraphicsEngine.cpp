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

namespace Atum
{

namespace GraphicsEngine
{

//-----------------------------------------------------------------------------
GraphicsEngine::GraphicsEngine(int argc, char *argv[])
{
    LowLevelGraphics::LowLevelAPI::Initialize(&argc, argv);

    LowLevelGraphics::WindowParameters params("Graphic Engine", 1024, 768, 0, 0);
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
    //todo : add visibility system outside and iterate on visible objects only

    //-----------------------------------------------------------------------------
    //Skybox
    DrawSkyBox(scene);
    //draw

    //-----------------------------------------------------------------------------
    //LowLevelGraphics::LowLevelAPI::ActivateWireframeMode();
    
    LowLevelGraphics::LowLevelAPI::EnableDepthRead();
    {
        //-----------------------------------------------------------------------------
        //Opaque objects
        LowLevelGraphics::LowLevelAPI::EnableDepthWrite();
        {
            LowLevelGraphics::LowLevelAPI::EnableBackFaceCulling();
            {
                DrawOpaqueObjects(scene);
            }
            LowLevelGraphics::LowLevelAPI::DisableBackFaceCulling();

            //-----------------------------------------------------------------------------
            //Opaque objects with holes (if we know the information?)
            //draw
        }
		DrawPointLightSphere(scene);
        LowLevelGraphics::LowLevelAPI::DisableDepthWrite();

        //-----------------------------------------------------------------------------
        //Alpha
        LowLevelGraphics::LowLevelAPI::EnableAlphaBlending();
        {
            //-----------------------------------------------------------------------------
            //Points
            LowLevelGraphics::LowLevelAPI::UnlockShaderPointSize();
            {
				//-----------------------------------------------------------------------------
				//Point clouds
				LowLevelGraphics::LowLevelAPI::SetAlphaBlendFunc();
				DrawPointClouds(scene);

				//-----------------------------------------------------------------------------
				//Particles
				LowLevelGraphics::LowLevelAPI::SetAdditiveBlendFunc();
				DrawParticles(scene);
			}
			LowLevelGraphics::LowLevelAPI::LockShaderPointSize();

            //-----------------------------------------------------------------------------
            // draw alpha objects
            //-----------------------------------------------------------------------------
			/////////////////////
			LowLevelGraphics::LowLevelAPI::SetAlphaBlendFunc();

            /////////////////////
            //draw alpha objects

        }
        LowLevelGraphics::LowLevelAPI::DisableAlphaBlending();
    }
	DrawSelectionBox(scene);
    LowLevelGraphics::LowLevelAPI::DisableDepthRead();
    //LowLevelGraphics::LowLevelAPI::DeactivateWireframeMode();
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
void GraphicsEngine::DrawSkyBox(SceneManager::Scene* scene)
{
	SceneManager::SkyBox *const skyBox = scene->GetSkyBox();
	if (skyBox)
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(skyBox->GetMaterial()->GetShaderList());
		
		SceneManager::Camera* const cam = scene->GetCurrentCamera();
		glm::mat4x4 viewMatrix = cam->GetViewMatrix();
		skyBox->UpdateViewMatrix(viewMatrix);

		skyBox->UpdateProjectionMatrix();

		LowLevelGraphics::LowLevelAPI::EnableTextureCubeMap();

		skyBox->UpdateTextureSkyBox();

		LowLevelGraphics::ShaderProgram* shaderProgram = skyBox->GetMaterial()->GetShaderList()->GetShaderProgram();

		LowLevelGraphics::LowLevelAPI::DrawSkyBox(skyBox->GetGeometry(), shaderProgram->GetProgramId());

		LowLevelGraphics::LowLevelAPI::DisableTextureCubeMap();

		LowLevelGraphics::LowLevelAPI::UnbindShaders();
	}
}

//-----------------------------------------------------------------------------
void GraphicsEngine::DrawOpaqueObjects(SceneManager::Scene* scene)
{
    std::vector<SceneManager::Object*>::iterator it = scene->GetBeginObjectList();
    std::vector<SceneManager::Object*>::iterator itEnd = scene->GetEndObjectList();

    SceneManager::Camera* const cam = scene->GetCurrentCamera();
    glm::mat4x4 viewMatrix = cam->GetViewMatrix();

    for(;it!=itEnd;++it)
    {
        (*it)->Update();

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
        (*it)->GetMaterial()->BindShaderParameters();

		// We render
        LowLevelGraphics::LowLevelAPI::DrawCall((*it)->GetGeometry(),shaderProgram->GetProgramId());

        // DEBUG PURPOSE
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(3,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,3,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,3);
        glEnd();

		(*it)->GetMaterial()->UnbindShaderParameters();
        LowLevelGraphics::LowLevelAPI::UnbindShaders();
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

//-----------------------------------------------------------------------------
void GraphicsEngine::DrawPointClouds(SceneManager::Scene* scene)
{
    std::vector<SceneManager::Object*>::iterator it = scene->GetBeginPointCloudList();
    std::vector<SceneManager::Object*>::iterator itEnd = scene->GetEndPointCloudList();

    for(;it!=itEnd;++it)
    {
		(*it)->Update();

		LowLevelGraphics::ShaderProgram* shaderProgram = (*it)->GetMaterial()->GetShaderList()->GetShaderProgram();
		LowLevelGraphics::LowLevelAPI::BindShaders((*it)->GetMaterial()->GetShaderList());

        glm::mat4x4 modelMatrix;
        (*it)->GetTransform()->GetMatrix(modelMatrix);

        shaderProgram->UpdateShaderParameter(LowLevelGraphics::MODELMATRIX,&modelMatrix[0][0],SHADER_MATRIX44);

        LowLevelGraphics::LowLevelAPI::DrawCallPointCloud((*it)->GetGeometry(), shaderProgram->GetProgramId());
        LowLevelGraphics::LowLevelAPI::UnbindShaders();
    }
}

void GraphicsEngine::DrawSelectionBox(SceneManager::Scene* scene)
{
	const UserInterface::UiManager& manager = UserInterface::UiManager::GetInstance();
	SceneManager::PerspectiveCamera* camera ( 
		dynamic_cast<SceneManager::PerspectiveCamera*>(scene->GetCurrentCamera()) );

	if ( manager.GetSelectedComponent() && camera )
	{
		glm::vec3 maxCorner( manager.GetSelectedComponent()->GetAABB().m_maxBounds );
		glm::vec3 minCorner( manager.GetSelectedComponent()->GetAABB().m_minBounds );

		glm::mat4x4 viewMatrix;
		camera->GetViewMatrix(viewMatrix);

		glm::mat4x4 perspectiveMatrix;
		camera->GetPerspectiveMat(perspectiveMatrix);

		LowLevelGraphics::LowLevelAPI::DrawBoundingBox(&viewMatrix[0][0], &perspectiveMatrix[0][0], minCorner, maxCorner);
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
