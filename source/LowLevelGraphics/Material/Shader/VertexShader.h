#ifndef LOWLEVELGRAPHICS_MATERIAL_VERTEXSHADER_H
#define LOWLEVELGRAPHICS_MATERIAL_VERTEXSHADER_H

#include "LowLevelGraphics/Material/Shader/Shader.h"

#define VERTEXSHADER_ENTRY_FUNCTION_NAME "vertex_shader"

namespace Atum
{

namespace SceneManager
{
	class ShaderList;
}

namespace LowLevelGraphics
{
	class VertexShader : public Shader
	{
		friend class SceneManager::ShaderList;

		public:
			~VertexShader(){};

		// <TOREACTIVATE>
		//private:
			VertexShader(const char* vertexShaderFileName, std::string args);
			
	};

}
}

#endif