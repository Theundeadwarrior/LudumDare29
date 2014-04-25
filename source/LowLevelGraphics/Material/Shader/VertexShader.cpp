#include "LowLevelGraphics/Material/Shader/VertexShader.h"
#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"

namespace Atum
{
namespace LowLevelGraphics
{

VertexShader::VertexShader(const char* vertexShaderFileName, std::string args)
{
    //todo : Add control over profile versions? Context? (actually uses current context)
    LowLevelAPI::CreateVertexShaderFromFile(m_shaderId, vertexShaderFileName, args);
}

}
}
