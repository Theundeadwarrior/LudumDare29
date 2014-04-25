#ifndef SCENEMANAGER_SHADERLIST_MANAGER_H
#define SCENEMANAGER_SHADERLIST_MANAGER_H

#include <map>
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Material/Material.h"

namespace Atum
{

namespace SceneManager
{
	class ShaderList;

	typedef std::map<ShaderListID, ShaderList*> ShaderListMap;

	class ShaderListManager
	{
		public:
			ShaderListManager();
			~ShaderListManager();

			ShaderListID		CreateShaderList	( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::bitset<MATERIALEFFECT_COUNT> shaderCompileFlags );
			void				RemoveShaderList	( ShaderListID shaderListID );
			ShaderList* const	GetShaderList		( ShaderListID shaderListID );
			void				ClearAll();

			ShaderListID GetShaderListIdFromFlags(std::bitset<MATERIALEFFECT_COUNT> flags);

		private:
			//void InsertShaderListWithId( ShaderList* const shaderList, ShaderListID id );
			ShaderListID InsertShaderList( ShaderList* const shaderList );

			ShaderListManager(ShaderListManager const&);
			void operator=(ShaderListManager const&);

			// Maps and id to a shaderList
			ShaderListMap m_shaderListMap;

			// Maps a variation to an id
			std::map<unsigned long int, ShaderListID> m_shaderVariationMap;

	};

}
}
#endif // SCENEMANAGER_SHADERLIST_MANAGER_H