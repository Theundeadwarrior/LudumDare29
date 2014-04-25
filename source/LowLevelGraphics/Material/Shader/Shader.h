#ifndef LOWLEVELGRAPHICS_MATERIAL_SHADER_H
#define LOWLEVELGRAPHICS_MATERIAL_SHADER_H

#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include <vector>



namespace Atum
{
namespace LowLevelGraphics
{
class Shader
{

public:
	virtual ~Shader() = 0{}
    const LowLevelAPI::ShaderId GetShaderId()const {return m_shaderId;}

protected:
    LowLevelAPI::ShaderId m_shaderId;

};

}
}

#endif
