#ifndef LOWLEVELGRAPHICS_CONTEXT_H
#define LOWLEVELGRAPHICS_CONTEXT_H

#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"

namespace Atum
{
namespace LowLevelGraphics
{

class Context
{
public:
    Context(LowLevelAPI::ShaderContext shaderContext, int contextId):m_shaderContext(shaderContext),m_id(contextId){}
    LowLevelAPI::ShaderContext GetShaderContext() {return m_shaderContext;}

private:
    LowLevelAPI::ShaderContext m_shaderContext;
    int m_id;
};

}
}

#endif