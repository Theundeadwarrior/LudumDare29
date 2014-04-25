#include "LowLevelGraphics/Material/Shader/FragmentShader.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"

namespace Atum
{
namespace LowLevelGraphics
{

//-----------------------------------------------------------------------------
FragmentShader::FragmentShader(const char* fragmentShaderFileName, std::string args)
{
    //todo : Add control over profile versions? Context? (actually uses current context)
    LowLevelAPI::CreateFragmentShaderFromFile(m_shaderId, fragmentShaderFileName, args);
}

}
}
