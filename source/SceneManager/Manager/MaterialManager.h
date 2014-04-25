#ifndef SCENEMANAGER_MATERIALMANAGER_H
#define SCENEMANAGER_MATERIALMANAGER_H

#include <map>
#include <vector>
#include <utility>
#include <string>
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
	class Material;
	struct MaterialParameters;
	class ShaderList;

	typedef std::map<MaterialID, Material*> MaterialMap;

	class MaterialManager
	{
		public:
			MaterialManager();
			~MaterialManager();

			MaterialID		CreateMaterial	( MaterialParameters materialParameters, ShaderListID shaderList);
			MaterialID		CreateMaterial	( ShaderListID shaderList);
			void			RemoveMaterial	( MaterialID materialID );
			Material* const	GetMaterial		( MaterialID materialID );
			void			ClearAll();

			std::vector<std::pair<int,std::string>>* GetLightingTechniques();

		private:
			//void InsertMaterialWithId( Material* const material, MaterialID id );
			MaterialID InsertMaterial( Material* const material );

			MaterialManager(MaterialManager const&);
			void operator=(MaterialManager const&);

			MaterialMap m_materialMap;

			// For UI purpose
			static std::vector<std::pair<int,std::string>> m_materialEffectList;
	};

}
}

#endif //SCENEMANAGER_MATERIALMANAGER_H
