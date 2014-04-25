#ifndef SCENEMANAGER_POINTLIGHT_H
#define SCENEMANAGER_POINTLIGHT_H

#include "GLM/include/glm/glm.hpp"

#include "Light.h"
#include "SceneManager/Utilities/Transform.h"

//namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{
	class PointLight : public Light
	{
		public:
			PointLight();
			PointLight(const LightBaseParams& baseParams, const Transform& transform, float radius);
			~PointLight();
			
			Transform* const GetTransform(){return &m_transform;}
			float GetRadius(){return m_radius;}

			void SetDiffuse(const glm::vec4& diffuse);
			void SetAmbient(const glm::vec4& ambient);
			void SetSpecular(const glm::vec4& specular);
			void SetTransform(const Transform& transform);
			void SetRadius(float radius);

			void GetPropertyList ( PropertyList& o_properties ) const;
			void UpdatePropertyList ( const PropertyList& i_properties );

			void UpdateAABB();
			void Update();

		private:
			Transform m_transform;
			float m_radius;
	};

} // namespace SceneManager
} // namespace Atum


#endif
