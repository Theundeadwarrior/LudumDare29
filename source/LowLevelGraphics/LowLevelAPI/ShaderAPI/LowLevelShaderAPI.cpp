#include "LowLevelGraphics/LowLevelAPI/ShaderAPI/LowLevelShaderAPI.h"
#include "LowLevelGraphics/LowLevelAPI/WindowAPI/LowLevelWindowAPI.h"

#include "glew/include/GL/glew.h"
#include "freeglut/include/GL/freeglut.h"

#include "SceneManager/Material/Material.h"

#include "LowLevelGraphics/Context/Context.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"

#include "Utilities/Debug/Debug.h"
#include <fstream>
#include <string>
#include <iostream>

namespace Atum
{
namespace LowLevelGraphics
{
namespace LowLevelAPI
{

//-----------------------------------------------------------------------------
void CreateNewContext()
{
	ATUM_ASSERT_MESSAGE(GetCurrentWindowId(),"Need a window to create a context");
	
	glewExperimental = GL_TRUE; 
	glewInit();
	ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to initialize glew");
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDrawBuffer(GL_FRONT_AND_BACK);
	glEnable(GL_POINT_SMOOTH);
	
	ShaderProgram::InitializeGlobalShaderParameters();
}

//-----------------------------------------------------------------------------
//todo : make a single CreateShaderProgramFromFile taking a ShaderSettings struct in parameter, ShaderSettings would have careful consideration of API macros
void CreateFragmentShaderFromFile(ShaderId& shaderId, const char* fragmentShaderFileName, std::string args)
{
    ATUM_ASSERT_MESSAGE(fragmentShaderFileName,"Shader name must not be null");

	std::ifstream shaderFile;
	shaderFile.open(fragmentShaderFileName);
	std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	if(shaderFile.fail())
	{
		ATUM_ASSERT_MESSAGE(false, "Shader file couldn't be read");
	}

	shaderId = glCreateShader(GL_FRAGMENT_SHADER); 
	shaderCode = args + shaderCode;
	const char* shaderChars = shaderCode.c_str();
	glShaderSource(shaderId,1,&shaderChars,NULL);

	glCompileShader(shaderId);

	// Compiling errors
	int CompilationStatus = 0;
	glGetShaderiv(shaderId,GL_COMPILE_STATUS,&CompilationStatus);
	ATUM_ASSERT_MESSAGE(CompilationStatus, "Fragment shader failed to compile.");

	std::cout << ShaderLog(shaderId) << std::endl;
}

//-----------------------------------------------------------------------------
//todo : make a single CreateShaderProgramFromFile taking a ShaderSettings struct in parameter, ShaderSettings would have careful consideration of API macros
void CreateVertexShaderFromFile(ShaderId& shaderId, const char* vertexShaderFileName, std::string args)
{
	ATUM_ASSERT_MESSAGE(vertexShaderFileName,"Shader name must not be null");

	std::ifstream shaderFile;
	shaderFile.open(vertexShaderFileName);
	bool test = shaderFile.fail();
	std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	if(shaderFile.fail())
	{
		ATUM_ASSERT_MESSAGE(false, "Shader file couldn't be read");
	}

	shaderId = glCreateShader(GL_VERTEX_SHADER); 
	shaderCode = args + shaderCode;
	const char* shaderChars =  shaderCode.c_str();

	glShaderSource(shaderId,1,&shaderChars,NULL);

	glCompileShader(shaderId);

	// Compiling errors
	int CompilationStatus = 0;
	glGetShaderiv(shaderId,GL_COMPILE_STATUS,&CompilationStatus);
	ATUM_ASSERT_MESSAGE(CompilationStatus, "Fragment shader failed to compile.");

	std::cout << ShaderLog(shaderId) << std::endl;
}

//-----------------------------------------------------------------------------
Atum::LowLevelGraphics::LowLevelAPI::ShaderProgramId CreateShaderProgram( ShaderId vertexId, ShaderId fragmentId )
{
	//Create the shader program and attach the two shaders to it.
	ShaderProgramId programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);

	glBindAttribLocation(programId, 0, "position");
	glBindAttribLocation(programId, 1, "normal");
	glBindAttribLocation(programId, 2, "texCoords");

	//Link the shader program
	glLinkProgram(programId);     

	int linkStatus = 0;
	glGetProgramiv(programId,GL_LINK_STATUS,&linkStatus);
	ATUM_ASSERT_MESSAGE(linkStatus, "Shaders couldn't be linked to the program");

	return programId;
}

//-----------------------------------------------------------------------------
// moved to shader program!!!
//-----------------------------------------------------------------------------
void DestroyShaderProgram(ShaderProgramId& shaderProgram)
{
    ATUM_ASSERT_MESSAGE(false,"METHOD DEPRECATED, USE THE DELETE IN SHADERPROGRAM INSTEAD");
}

//-----------------------------------------------------------------------------
void BindShaders( SceneManager::ShaderList* const shaderList )
{
	glUseProgram(shaderList->GetShaderProgram()->GetProgramId());
}

//-----------------------------------------------------------------------------
// Low level linking with a uniform buffer parameter and a shader
//-----------------------------------------------------------------------------
void ConnectGlobalShaderParameters(const ShaderProgramId programId, const ShaderParameterId blockIndexProgram, const ShaderParameterId shaderParameter)
{
	glUniformBlockBinding(programId, blockIndexProgram, shaderParameter);
	GLenum error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");
}

//-----------------------------------------------------------------------------
ShaderParameterId GetParameterLocation(const ShaderProgramId shaderProgram, const char* paramName)
{
	ShaderParameterId shaderParameter = glGetUniformLocation(shaderProgram, paramName);
	ATUM_ASSERT_MESSAGE(shaderParameter != -1, "Fail to get uniform location.");
    return shaderParameter;
}

//-----------------------------------------------------------------------------
// Get the location of a global parameter
//-----------------------------------------------------------------------------
uintShaderParameterId GetGlobalParameterLocation(const ShaderProgramId shaderProgram, const char* paramName)
{
	uintShaderParameterId shaderParameter = glGetUniformBlockIndex(shaderProgram, paramName);
	ATUM_ASSERT_MESSAGE(shaderParameter != -1, "Fail to get location of a global shader param");
	return shaderParameter;
}

//-----------------------------------------------------------------------------
// Creates a buffer for a global parameter and associates it with a certain
// binding point (we use the enum for global param so we don't have
// overlaps on the ids of the bindingpoints.
//-----------------------------------------------------------------------------
uintShaderParameterId CreateGlobalShaderParameter(unsigned int bindingPoint, unsigned int size)
{
	uintShaderParameterId buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	GLenum error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");

	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
	error = glGetError();
	ATUM_ASSERT_MESSAGE(!error, "Failed to update a global shader param");
	return buffer;
}

//-----------------------------------------------------------------------------
std::string ShaderLog(ShaderId shaderId)
{   
	int LogLength = 0;
	glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&LogLength);

	char *Log = new char[LogLength];

	int ReturnedLength = 0;
	glGetShaderInfoLog(shaderId, LogLength, &ReturnedLength, Log);

	std::string RetStr(Log);
	delete[] Log;

	return RetStr;
}

}
}
}
