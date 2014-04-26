#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"
#include "SceneManager/SceneManager.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"

namespace Atum
{
namespace SceneManager
{
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

	void GamePlayObject::Update()
	{
	}

	void GamePlayObject::SetXY(float x, float y)
	{
		m_currentPosition[0] = x;
		m_currentPosition[1] = y;
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
	}

	void GamePlayObject::SetScaleXY(float x, float y)
	{
		m_scale[0] = x;
		m_scale[1] = y;
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);
	}

	void GamePlayObject::SetRelativeXY(float x, float y)
	{
		m_currentPosition[0] += x;
		m_currentPosition[1] += y;
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("translation", &m_currentPosition, SHADER_FLOAT4);
	}

	void GamePlayObject::SetRelativeScaleXY(float x, float y)
	{
		m_scale[0] += x;
		m_scale[1] += y;
		GetMaterial()->GetShaderList()->GetShaderProgram()->UpdateShaderParameterWithName("scale", &m_scale, SHADER_FLOAT4);
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
	
	namespace Hack
	{
		ShaderListID LocalLoadShader()
		{
			static ShaderListID standardGameplayObjectShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/StandardGameplayObject.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);
			LowLevelGraphics::LowLevelAPI::BindShaders(SceneManager::GetInstance().GetShaderListManager()->GetShaderList(standardGameplayObjectShaderID));
			return standardGameplayObjectShaderID;
		}
	}

	ShaderListID GamePlayObject::GetShaderID()
	{
		static ShaderListID standardGameplayObjectShaderID = Hack::LocalLoadShader();
		return standardGameplayObjectShaderID;
	}

	GeometryID GamePlayObject::GetQuadID()
	{
		static ShaderListID standardGameplayObjectGeometryID = SceneManager::GetInstance().GetGeometryManager()->CreateGeometry(Utilities::CreatePlaneGeometry(1.0f,1.0f));
		return standardGameplayObjectGeometryID;
	}

} // namespace SceneManager
} // namespace Atum
