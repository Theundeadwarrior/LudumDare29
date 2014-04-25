#ifndef SCENEMANAGER_LIGHT_H
#define SCENEMANAGER_LIGHT_H

#include "GLM/include/glm/glm.hpp"

#include "SceneManager/Component/Component.h"

namespace Atum { namespace SceneManager { class PropertyList; }}

namespace Atum
{
namespace SceneManager
{
	struct LightBaseParams
	{
		glm::vec4 diffuse;
		glm::vec4 ambient;
		glm::vec4 specular;

		LightBaseParams()
		: diffuse(1,1,1,1)
		, ambient(0,0,0,1)
		, specular(1,1,1,1)
		{
		}

		LightBaseParams(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular)
		: diffuse(diffuse)
		, ambient(ambient)
		, specular(specular)
		{
		}

	};

	class Light : public Component
	{
		public:
			Light();
			Light(LightBaseParams params);
			virtual ~Light()=0;
			
			glm::vec4 GetDiffuse(){return m_baseLightParams.diffuse;}
			glm::vec4 GetAmbient(){return m_baseLightParams.ambient;}
			glm::vec4 GetSpecular(){return m_baseLightParams.specular;}

			virtual void SetDiffuse(const glm::vec4& diffuse);
			virtual void SetAmbient(const glm::vec4& ambient);
			virtual void SetSpecular(const glm::vec4& specular);

			int GetIndex(){return m_index;}
			void SetIndex(int index){m_index = index;}

		protected:
			LightBaseParams m_baseLightParams;
			int m_index;
	};

} // namespace SceneManager
} // namespace Atum


#endif
