#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"
#include "SceneManager/SceneManager.h"

#include "SceneManager/Scene/Scene.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"

#include "SceneManager/Objects/GameplayObjects/Background.h"

namespace Atum
{
namespace SceneManager
{
	float GamePlayObject::ms_cameraY = 0.0f;

	GamePlayObject::GamePlayObject()
		: m_isPositionAffectedByLevel(true)
		, m_currentPosition(glm::vec4(0,0,0,0))
	    , m_scale(glm::vec4(1,1,1,1))
	{

	}

	GamePlayObject::GamePlayObject(const glm::vec4& position, const glm::vec4& scale)
		: m_isPositionAffectedByLevel(true)
		, m_currentPosition(position)
		, m_scale(scale)
	{
	}

	GamePlayObject::~GamePlayObject()
	{}

	void GamePlayObject::Init()
	{
		m_materialID = GetMaterialID();
		m_geometryID = GetQuadID();
		UpdateAABB();
	}

	void GamePlayObject::BindShaderParameters()
	{
		LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(GetShaderID()));
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("cameraY", &ms_cameraY, SHADER_FLOAT);

		GetMaterial()->BindDiffuseMapToShader();
	}

	void GamePlayObject::Update()
	{
		Scene* scene = SceneManager::GetInstance().GetCurrentScene();
		
		std::list<Object*>::iterator it = scene->GetBeginObjectList();
		std::list<Object*>::iterator itEnd = scene->GetEndObjectList();

		for(;it!=itEnd;++it)
		{
			if(GetGameplayObjectType() != GamePlayObjectType_Platform)
			{
				if(Intersect(static_cast<GamePlayObject*>(*it)) != GamePlayObjectType_Invalid)
				{
					break;
				}
			}
		}
	}

	void GamePlayObject::SetXY(float x, float y)
	{
		m_currentPosition[0] = x;
		m_currentPosition[1] = y;
		
	}

	void GamePlayObject::SetScaleXY(float x, float y)
	{
		m_scale[0] = x;
		m_scale[1] = y;
	}

	void GamePlayObject::SetRelativeXY(float x, float y)
	{
		m_currentPosition[0] += x;
		m_currentPosition[1] += y;
		
	}

	void GamePlayObject::SetRelativeScaleXY(float x, float y)
	{
		m_scale[0] += x;
		m_scale[1] += y;
	}

	void GamePlayObject::GetPropertyList( PropertyList& o_properties )
	{
		Object::GetPropertyList(o_properties); //get the parent properties
		//get the child properties

	}

	void GamePlayObject::UpdatePropertyList( PropertyList& i_properties )
	{
		Object::UpdatePropertyList( i_properties ); //update the parent properties
		//update the child properties
	}
	
	ShaderListID GamePlayObject::GetShaderID()
	{
		static ShaderListID standardGameplayObjectShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/StandardGameplayObject.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);;
		return standardGameplayObjectShaderID;
	}

	GeometryID GamePlayObject::GetQuadID()
	{
		static ShaderListID standardGameplayObjectGeometryID = SceneManager::GetInstance().GetGeometryManager()->CreateGeometry(Utilities::CreatePlaneGeometry(1.0f,1.0f));
		return standardGameplayObjectGeometryID;
	}

} // namespace SceneManager
} // namespace Atum
