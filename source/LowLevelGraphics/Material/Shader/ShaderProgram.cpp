#include "LowLevelGraphics/Material/Shader/ShaderProgram.h"

namespace Atum
{
namespace LowLevelGraphics
{
std::vector<LowLevelAPI::uintShaderParameterId> ShaderProgram::m_globalShaderParams;

//-----------------------------------------------------------------------------
// Creates the global parameter list.
//-----------------------------------------------------------------------------
void ShaderProgram::InitializeGlobalShaderParameters()
{
    if(ShaderProgram::m_globalShaderParams.empty())
    {
		// Camera Parameters
		ShaderProgram::m_globalShaderParams.resize(GLOBALSHADERPARAMETER_COUNT);
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::VIEWMATRIX] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, sizeof(glm::mat4));
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::PROJECTIONMATRIX] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX, sizeof(glm::mat4));

		// Light Parameters
		const int numberOfPointLights = 5;
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSDIFFUSE] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSDIFFUSE, sizeof(glm::vec4) * numberOfPointLights); 
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSAMBIENT] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSAMBIENT, sizeof(glm::vec4) * numberOfPointLights); 
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSSPECULAR] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSSPECULAR, sizeof(glm::vec4) * numberOfPointLights);
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSTRANSFORM] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSTRANSFORM, sizeof(glm::mat4) * numberOfPointLights); 
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSRADIUS] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSRADIUS, sizeof(float) * numberOfPointLights); 	
		ShaderProgram::m_globalShaderParams[LowLevelGraphics::POINTLIGHTSSIZE] = LowLevelAPI::CreateGlobalShaderParameter(LowLevelGraphics::POINTLIGHTSSIZE, sizeof(int));

	}
}

//-----------------------------------------------------------------------------
// Update a global parameter with an index. Use it for passing parameters
// that are in an array.
//-----------------------------------------------------------------------------
void ShaderProgram::UpdateGlobalShaderParameter(const GlobalShaderParameter shaderParam, const void* val, const int index, const LowLevelAPI::ShaderParameterType& shaderParamType)
{
	LowLevelAPI::UpdateGlobalShaderParameter(ShaderProgram::m_globalShaderParams[shaderParam], val, index, shaderParamType);
}

//-----------------------------------------------------------------------------
void ShaderProgram::UpdateGlobalShaderParameter(const GlobalShaderParameter shaderParam, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType)
{
    LowLevelAPI::UpdateGlobalShaderParameter(ShaderProgram::m_globalShaderParams[shaderParam], val, 0, shaderParamType);
}

//-----------------------------------------------------------------------------
void ShaderProgram::AddShaderParameter(const char* paramName)
{
    m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, paramName));
}

//-----------------------------------------------------------------------------
void ShaderProgram::UpdateShaderParameter(const unsigned int id, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType)const
{
    LowLevelAPI::UpdateShaderParameter(m_shaderParams[id], val, shaderParamType);
}


void ShaderProgram::UpdateShaderParameterWithName( const char* name, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType ) const
{
	LowLevelAPI::UpdateShaderParameter(LowLevelAPI::GetParameterLocation(m_shaderProgramId, name), val, shaderParamType);
}


//-----------------------------------------------------------------------------
// Connects the shader to the global parameters in the shared video memory
//-----------------------------------------------------------------------------
void ShaderProgram::ConnectToGlobalShaderParameters()
{
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, VIEW_MATRIX_NAME), LowLevelGraphics::VIEWMATRIX);
    LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, PROJECTION_MATRIX_NAME), LowLevelGraphics::PROJECTIONMATRIX);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSDIFFUSE_NAME), LowLevelGraphics::POINTLIGHTSDIFFUSE);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSAMBIENT_NAME), LowLevelGraphics::POINTLIGHTSAMBIENT);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSSPECULAR_NAME), LowLevelGraphics::POINTLIGHTSSPECULAR);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSRADIUS_NAME), LowLevelGraphics::POINTLIGHTSRADIUS);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSTRANSFORM_NAME), LowLevelGraphics::POINTLIGHTSTRANSFORM);
	LowLevelAPI::ConnectGlobalShaderParameters(m_shaderProgramId, LowLevelAPI::GetGlobalParameterLocation(m_shaderProgramId, POINTLIGHTSSIZE_NAME), LowLevelGraphics::POINTLIGHTSSIZE);
}

//-----------------------------------------------------------------------------
// Creates the parameter for the possible local shader parameters
//-----------------------------------------------------------------------------
void ShaderProgram::InitLocalShaderParameters()
{
	// <materialvariation> : if def tous les parametres
	m_shaderParams.reserve(LowLevelGraphics::LOCALSHADERPARAMETER_COUNT);
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, MODEL_MATRIX_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, MODELVIEW_MATRIX_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, NORMAL_MATRIX_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, DIFFUSEMAP_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, PARALLAXMAP_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, PARALLAXHEIGHTSCALE_NAME));
	m_shaderParams.push_back(LowLevelAPI::GetParameterLocation(m_shaderProgramId, PARALLAXHEIGHTBIAS_NAME));
}

//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::string args)
{
	m_vertexShader = new LowLevelGraphics::VertexShader(vertexShaderFileName, args);
	m_fragmentShader = new LowLevelGraphics::FragmentShader(fragmentShaderFileName, args);
	m_shaderProgramId = LowLevelAPI::CreateShaderProgram(m_vertexShader->GetShaderId(), m_fragmentShader->GetShaderId());
	ConnectToGlobalShaderParameters();
	InitLocalShaderParameters();
}

//-----------------------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
	if(m_shaderProgramId)
	{
		if(m_vertexShader)
		{
			glDetachShader(m_vertexShader->GetShaderId(), GetProgramId());
			delete m_vertexShader;
			m_vertexShader = NULL;
		}
		if(m_fragmentShader)
		{
			glDetachShader(m_fragmentShader->GetShaderId(), GetProgramId());
			delete m_fragmentShader;
			m_fragmentShader = NULL;
		}
	}
}

}
}
