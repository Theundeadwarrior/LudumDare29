#ifndef LOWLEVELGRAPHICS_MATERIAL_FRAGMENTSHADER_H
#define LOWLEVELGRAPHICS_MATERIAL_FRAGMENTSHADER_H

#include "LowLevelGraphics/Material/Shader/Shader.h"

#define FRAGMENTSHADER_ENTRY_FUNCTION_NAME "fragment_shader"

namespace Atum
{

namespace SceneManager
{
	class ShaderList;
}

namespace LowLevelGraphics                                                                                            
{

	class FragmentShader : public Shader
	{
		friend class SceneManager::ShaderList;

		public:
			~FragmentShader(){};
		// <TOREACTIVATE>
		//private:
			FragmentShader(const char* fragmentShaderFileName, std::string args);
	};

}
}

#endif