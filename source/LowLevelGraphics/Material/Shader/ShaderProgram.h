#ifndef LOWLEVELGRAPHICS_MATERIAL_SHADERPROGRAM_H
#define LOWLEVELGRAPHICS_MATERIAL_SHADERPROGRAM_H

#include <vector>

#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include "LowLevelGraphics/Material/Shader/FragmentShader.h"
#include "LowLevelGraphics/Material/Shader/VertexShader.h"

// Shader Parameter Names
#define VIEW_MATRIX_NAME "ViewMatrix"
#define PROJECTION_MATRIX_NAME "ProjectionMatrix"
#define MODEL_MATRIX_NAME "ModelMatrix"
#define MODELVIEW_MATRIX_NAME "ModelViewMatrix"
#define NORMAL_MATRIX_NAME "NormalMatrix"
#define DIFFUSEMAP_NAME "DiffuseMap"
#define PARALLAXMAP_NAME "ParallaxMap"
#define PARALLAXHEIGHTSCALE_NAME "ParallaxHeightScale"
#define PARALLAXHEIGHTBIAS_NAME "ParallaxHeightBias"
#define POINTLIGHTSDIFFUSE_NAME "PointLightsDiffuse"
#define POINTLIGHTSAMBIENT_NAME "PointLightsAmbient"
#define POINTLIGHTSSPECULAR_NAME "PointLightsSpecular"
#define POINTLIGHTSRADIUS_NAME "PointLightsRadius"
#define POINTLIGHTSTRANSFORM_NAME "PointLightsTransform"
#define POINTLIGHTSSIZE_NAME "PointLightsCount"

namespace Atum
{
namespace LowLevelGraphics
{

//one value for all shaders
//-----------------------------------------------------------------------------
enum GlobalShaderParameter
{
    VIEWMATRIX = 0,
    PROJECTIONMATRIX,
	POINTLIGHTSDIFFUSE,
	POINTLIGHTSAMBIENT,
	POINTLIGHTSSPECULAR,
	POINTLIGHTSRADIUS,
	POINTLIGHTSTRANSFORM,
	POINTLIGHTSSIZE,
    GLOBALSHADERPARAMETER_COUNT
};

//-----------------------------------------------------------------------------
enum LocalShaderParameter
{
	MODELMATRIX = 0,
	MODELVIEWMATRIX,
	NORMALMATRIX,
	DIFFUSEMAP,
	PARALLAXMAP,
	PARALLAXHEIGHTSCALE,
	PARALLAXHEIGHTBIAS,
	LOCALSHADERPARAMETER_COUNT
};

//-----------------------------------------------------------------------------
class ShaderProgram
{
// Static global stuff
public:
	static void InitializeGlobalShaderParameters();
    static void UpdateGlobalShaderParameter(const GlobalShaderParameter shaderParam, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType);
	static void UpdateGlobalShaderParameter(const GlobalShaderParameter shaderParam, const void* val, const int index, const LowLevelAPI::ShaderParameterType& shaderParamType);
private:
    static std::vector<LowLevelAPI::uintShaderParameterId> m_globalShaderParams;

// Class stuff
public:
	ShaderProgram( const char* vertexShaderFileName, const char* fragmentShaderFileName, std::string args);
    ~ShaderProgram();

    void AddShaderParameter(const char* paramName);
	void UpdateShaderParameter(const unsigned int it, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType) const;
    void UpdateShaderParameterWithName(const char* name, const void* val, const LowLevelAPI::ShaderParameterType& shaderParamType) const;

    LowLevelAPI::ShaderProgramId GetProgramId()const {return m_shaderProgramId;}
	LowLevelGraphics::FragmentShader* const GetFragmentShader() {return m_fragmentShader;}
	LowLevelGraphics::VertexShader* const GetVertexShader() {return m_vertexShader;}

private:
	void ConnectToGlobalShaderParameters();
	void InitLocalShaderParameters();

private:
    std::vector<LowLevelAPI::ShaderParameterId> m_shaderParams;
	LowLevelGraphics::FragmentShader* m_fragmentShader;
	LowLevelGraphics::VertexShader* m_vertexShader;

	LowLevelAPI::ShaderProgramId m_shaderProgramId;

};

}
}

#endif
