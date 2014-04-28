#ifndef SCENEMANAGER_OBJECT_CPP
#define SCENEMANAGER_OBJECT_CPP

#include "Object.h"

#include "Utilities/IdGenerator/IdGenerator.h"

#include "SceneManager/SceneManager.h"
#include "SceneManager/Manager/MaterialManager.h"
#include "SceneManager/Manager/GeometryManager.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Properties/PropertyList.h"
#include "SceneManager/Properties/Property.h"
#include "Events/EventManager.h"

namespace Atum
{
namespace SceneManager
{
	Object::Object()
		: Component()
		, m_state(E_Ok)
	{
		
	}

	Object::Object(MaterialID materialID, GeometryID geomId, const Transform& transform)
		: Component()
		, m_transform(transform)
		, m_geometryID(geomId)
		, m_materialID(materialID)
		, m_state(E_Ok)
	{
		UpdateAABB();
	}

	Object::Object( MaterialID materialID, GeometryID geomId, const Transform & transform , const Utilities::AABB & aabb)
		: Component()
		, m_materialID(materialID)
		, m_geometryID(geomId)
		, m_transform(transform)
		, m_state(E_Ok)
	{
		m_aabb = aabb;
	}

	Object::~Object()
	{
		ATUM_ASSERT_MESSAGE(m_state == E_ToDelete, "Trying to delete an object that wasn't flagged to be deleted");
	}

	Material* const Object::GetMaterial()
	{
		return SceneManager::GetInstance().GetMaterialManager()->GetMaterial(m_materialID);
	}

	const LowLevelGraphics::Geometry* const Object::GetGeometry()
	{
		return SceneManager::GetInstance().GetGeometryManager()->GetGeometry(m_geometryID);
	}

	Transform* const Object::GetTransform()
	{
		return &m_transform;
	}

	void Object::UpdateAABB()
	{
		GeometryManager* const gm = SceneManager::GetInstance().GetGeometryManager();
		const LowLevelGraphics::Geometry* const geom = gm->GetGeometry(m_geometryID);

		m_aabb.UpdateBoundingBox(*(geom->GetOBB()), m_transform);
	}

	void Object::Update()
	{
		m_transform.UpdateMatrices();
		UpdateAABB();
	}

	void Object::GetPropertyList( PropertyList& o_properties ) const
	{
	}

	void Object::UpdatePropertyList( const PropertyList& i_properties )
	{
	}

} // namespace SceneManager
} // namespace Atum


#endif
