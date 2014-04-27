#ifndef SCENEMANAGER_OBJECT_H
#define SCENEMANAGER_OBJECT_H

#include "GLM/include/glm/glm.hpp"
#include "LowLevelGraphics/Geometry/Geometry.h"

#include "SceneManager/Component/Component.h"
#include "SceneManager/Utilities/Transform.h"
#include "SceneManager/Material/Material.h"

#include "Utilities/Physic/AABB.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{
	class Object : public Component
	{
	public:
		enum State
		{
			E_Ok,
			E_Invalid,
			E_ToDelete
		};
		
		Object(MaterialID materialID, GeometryID geomId, const Transform& transform);
		Object(MaterialID materialID, GeometryID geomId, const Transform& transform, const Utilities::AABB & aabb);
		virtual ~Object();

		virtual void GetPropertyList(PropertyList& o_properties) const;
		virtual void UpdatePropertyList(const PropertyList& i_properties);

		virtual void BindShaderParameters(){ GetMaterial()->BindShaderParameters(); }

		void SetMaterialID(MaterialID mId){ m_materialID = mId; }

		const LowLevelGraphics::Geometry* const GetGeometry();
		Material* const GetMaterial();
		Transform* const GetTransform();

		void SetState(State state) { m_state = state; }
		State GetState() { return m_state; }

		void UpdateAABB();
		virtual void Update();

		protected:
			Object();
			Transform m_transform;
			GeometryID m_geometryID;
			MaterialID m_materialID;
			State m_state;
	
	};

} // namespace SceneManager
} // namespace Atum


#endif
