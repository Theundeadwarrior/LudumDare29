#include "SceneManager/Objects/GameplayObjects/GamePlayObject.h"
#include "SceneManager/SceneManager.h"

#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"

namespace Atum
{
namespace SceneManager
{
	GamePlayObject::GamePlayObject()
		: m_isPositionAffectedByLevel(true)
		, m_currentPosition(glm::vec4(0,0,0,1))
	    , m_scale(1.0f)
	{

	}

	GamePlayObject::~GamePlayObject()
	{}

	void GamePlayObject::Init()
	{
		m_materialID = GetMaterial();
		m_geometryID = GetQuad();
		UpdateAABB();
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

	ShaderListID GamePlayObject::GetShader()
	{
		static ShaderListID standardGameplayObjectShaderID = SceneManager::GetInstance().GetShaderListManager()->CreateShaderList("../../data/shaders/StandardGameplayObject.vx", "../../data/shaders/AlphaTestedTexture.fg", NULL);; 
		return standardGameplayObjectShaderID;
	}
	GeometryID GamePlayObject::GetQuad()
	{
		static ShaderListID standardGameplayObjectGeometryID = SceneManager::GetInstance().GetGeometryManager()->CreateGeometry(Utilities::CreatePlaneGeometry(1.0f,1.0f));
		return standardGameplayObjectGeometryID;
	}

} // namespace SceneManager
} // namespace Atum
