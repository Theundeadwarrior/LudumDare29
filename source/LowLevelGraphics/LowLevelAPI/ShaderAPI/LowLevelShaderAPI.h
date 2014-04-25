#ifndef LOWLEVELGRAPHICS_LOWLEVELAPI_SHADERAPI_LOWLEVELSHADERAPI_H
#define LOWLEVELGRAPHICS_LOWLEVELAPI_SHADERAPI_LOWLEVELSHADERAPI_H

#include "glew/include/GL/glew.h"
#include "Cg/include/cgGL.h"
#include "Utilities/Debug/Debug.h"
#include <vector>
#include "SceneManager/Lights/PointLight.h"

#define SHADER_FLOAT CG_FLOAT
#define SHADER_MATRIX44 CG_FLOAT4x4
#define SHADER_MATRIX33 CG_FLOAT3x3
#define SHADER_SAMPLER2D CG_SAMPLER2D
#define SHADER_FLOAT4 CG_FLOAT4
#define SHADER_INT CG_INT
#define SHADER_SAMPLERCUBE CG_SAMPLERCUBE

//Types of Light params
#define SHADER_LIGHT_DIFFUSE SHADER_FLOAT4
#define SHADER_LIGHT_AMBIENT SHADER_FLOAT4
#define SHADER_LIGHT_SPECULAR SHADER_FLOAT4
#define SHADER_LIGHT_RADIUS SHADER_FLOAT
#define SHADER_LIGHT_TRANSFORM SHADER_MATRIX44

namespace Atum
{

namespace SceneManager
{
	class ShaderList;
}

namespace LowLevelGraphics
{

namespace LowLevelAPI
{

typedef _CGcontext *ShaderContext;
typedef unsigned int ShaderId;
typedef unsigned int ShaderProgramId;
typedef unsigned int uintShaderParameterId;
typedef int ShaderParameterId;
typedef CGtype ShaderParameterType;

void CreateNewContext();
void CreateFragmentShaderFromFile(ShaderId& shaderId, const char* fragmentShaderFileName, std::string args);
void CreateVertexShaderFromFile(ShaderId& shaderId, const char* vertexShaderFileName, std::string args);
ShaderProgramId CreateShaderProgram(ShaderId vertexId, ShaderId fragmentId);
void DestroyShaderProgram(ShaderId vertexId, ShaderId fragmentId, ShaderProgramId shaderProgram);
ShaderParameterId GetParameterLocation(const ShaderProgramId shaderProgram, const char* paramName);

uintShaderParameterId GetGlobalParameterLocation(const ShaderProgramId shaderProgram, const char* paramName);// now only on glsl
uintShaderParameterId CreateGlobalShaderParameter(unsigned int bindingPoint, unsigned int size);
void ConnectGlobalShaderParameters(const ShaderProgramId programId, const ShaderParameterId blockIndexProgram, const ShaderParameterId shaderParameter);
void UpdateShaderParameter(const ShaderParameterId shaderParameter, const void* val, const int index, const ShaderParameterType& shaderParamType);
void UpdateGlobalShaderParameter(const ShaderParameterId shaderParam, const void* val, const int index, const ShaderParameterType& shaderParamType);

// needs reactivation
void EnableTextureShaderParameter(const ShaderParameterId shaderParameter);
void DisableTextureShaderParameter(const ShaderParameterId shaderParameter);

// Invariable
void BindShaders( SceneManager::ShaderList* const shaderList );
void UnbindShaders();
void UnlockShaderPointSize();
void LockShaderPointSize();

std::string ShaderLog(ShaderId shaderId);


//-----------------------------------------------------------------------------
inline void UnbindShaders()
{
	glUseProgram(NULL);
}

//-----------------------------------------------------------------------------
// Would be best if we could pass the size of the memory we want to input into 
// the buffer. That way, we could pass global structs to the shader and that
// would be useful for the lights.
//-----------------------------------------------------------------------------
inline void UpdateGlobalShaderParameter(const ShaderParameterId shaderParam, const void* val, const int index, const ShaderParameterType& shaderParamType)
{
	glBindBuffer(GL_UNIFORM_BUFFER, shaderParam);

	GLenum error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");

	switch(shaderParamType)
{
	case SHADER_FLOAT:
		{
			glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(float), sizeof(float), val);
			break;
}

	case SHADER_MATRIX33:
		{
			glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(glm::mat3), sizeof(glm::mat3),val);
			break;
		}
	case SHADER_MATRIX44:
		{
			glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4),val);
			break;
		}
	case SHADER_SAMPLER2D:
		{
			ATUM_ASSERT_MESSAGE(false, "Samplers not supported in global parameters");
			break;
		}
	case SHADER_FLOAT4:
		{
			glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(glm::vec4), sizeof(glm::vec4),val);
			break;
		}
	case SHADER_INT:
		{
			glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(int), sizeof(int),val);
			break;
		}
	default:
{
			ATUM_ASSERT_MESSAGE(false, "Shader Parameter type not supported");
			break;
		}
	}
	error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");
}

//-----------------------------------------------------------------------------
inline void UpdateShaderParameter(const ShaderParameterId shaderParam, const void* val, const ShaderParameterType& shaderParamType)
{
    switch(shaderParamType)
    {
    case SHADER_FLOAT:
        {
			glUniform1f(shaderParam, *reinterpret_cast<const float*>(val));
            break;
        }

	case SHADER_MATRIX33:
        {
			glUniformMatrix3fv(shaderParam, 1, false, reinterpret_cast<const float*>(val));
            break;
        }
	case SHADER_MATRIX44:
        {
			glUniformMatrix4fv(shaderParam, 1, false, reinterpret_cast<const float*>(val));
            break;
        }
	case SHADER_SAMPLER2D:
		{
			glUniform1i(shaderParam, *reinterpret_cast<const int*>(val));
			break;
		}
	case SHADER_SAMPLERCUBE:
		{
			glUniform1i(shaderParam, *reinterpret_cast<const int*>(val));
			break;
		}
	case SHADER_FLOAT4:
		{
			glUniform4fv(shaderParam, 1, reinterpret_cast<const float*>(val));
			break;
		}
	case SHADER_INT:
		{
			glUniform1i(shaderParam, *reinterpret_cast<const int*>(val));
			break;
		}
    default:
        {
            ATUM_ASSERT_MESSAGE(false, "Shader Parameter type not supported");
            break;
        }
    }

	GLuint error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a local shader param");
}

//-----------------------------------------------------------------------------
inline void EnableTextureShaderParameter(const ShaderParameterId shaderParameter)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,shaderParameter);
    //CGerror cgerror;
    //ATUM_ASSERT_MESSAGE(shaderParameter, "Shader parameter must not be null");
    //cgGLEnableTextureParameter(shaderParameter);
    //ATUM_ASSERT(!cgGetLastErrorString(&cgerror));
}

//-----------------------------------------------------------------------------
inline void DisableTextureShaderParameter(const ShaderParameterId shaderParameter)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,NULL);
    //CGerror cgerror;
    //ATUM_ASSERT_MESSAGE(shaderParameter, "Shader parameter must not be null");
    //cgGLDisableTextureParameter(shaderParameter);
    //ATUM_ASSERT(!cgGetLastErrorString(&cgerror));
}

//-----------------------------------------------------------------------------
inline void UnlockShaderPointSize()
{
	glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to unlock point size");
}

//-----------------------------------------------------------------------------
inline void LockShaderPointSize()
{
    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SMOOTH);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to lock point size");
}

}
}
}
#endif
