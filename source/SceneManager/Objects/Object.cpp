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
	Object::Object( MaterialID materialID, GeometryID geomId, const Transform& transform )
		:Component(),
		m_transform(transform),
		m_geometryID(geomId),
		m_materialID(materialID)
	{
		UpdateAABB();
	}

	Object::Object( MaterialID materialID, GeometryID geomId, const Transform & transform , const Utilities::AABB & aabb)
		: Component(),
		m_materialID(materialID),
		m_geometryID(geomId),
		m_transform(transform)
	{
		m_aabb = aabb;
	}

	Object::~Object()
	{}

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
		Property* name = new Property( COMP_PROP_NAME, GetName() );
		o_properties.AddProperty(name);
		
		Property* position = new Property( COMP_PROP_POSITION, m_transform.GetPosition() );
		o_properties.AddProperty(position);

		Property* scaleP = new Property( COMP_PROP_SCALE, m_transform.GetScale() );
		o_properties.AddProperty(scaleP);

		Property* rotation = new Property( COMP_PROP_ROTATION, m_transform.GetRotation() );
		o_properties.AddProperty(rotation);
	}

	void Object::UpdatePropertyList( const PropertyList& i_properties )
	{
		const Property* name = i_properties.GetProperty(COMP_PROP_NAME);
		if ( name )
		{
			name->GetValue(m_name);
		}
		const Property* position = i_properties.GetProperty(COMP_PROP_POSITION);
		if ( position )
		{
			glm::vec3 newPos;
			position->GetValue(newPos);
			m_transform.SetTranslate(newPos);
		}
		const Property* scaleP = i_properties.GetProperty(COMP_PROP_SCALE);
		if ( scaleP )
		{
			glm::vec3 newScale;
			scaleP->GetValue(newScale);
			m_transform.SetScale(newScale);
		}
		const Property* rotation = i_properties.GetProperty(COMP_PROP_ROTATION);
		if ( rotation )
		{
			glm::quat newRotation;
			rotation->GetValue(newRotation);
			m_transform.SetRotation(newRotation);
		}
	}

} // namespace SceneManager
} // namespace Atum


#endif
