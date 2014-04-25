#ifndef SCENEMANAGER_SKYBOX_H
#define SCENEMANAGER_SKYBOX_H

#include "SceneManager/Material/Material.h"
#include "LowLevelGraphics/Geometry/Geometry.h"

namespace Atum
{
namespace SceneManager
{
	class SkyBox
	{
		public:
			SkyBox(MaterialID materialID, GeometryID geometryID);
			~SkyBox();

			Material* const GetMaterial();
			const LowLevelGraphics::Geometry* const GetGeometry();
			void UpdateViewMatrix(glm::mat4 & viewMatrix);
			void UpdateProjectionMatrix();
			void UpdateTextureSkyBox();

		protected:
			MaterialID m_materialID;
			GeometryID m_geometryID;
	};

} // namespace SceneManager
} // namespace Atum


#endif
