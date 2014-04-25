#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "LowLevelGraphics/LowLevelAPI/WindowAPI/LowLevelWindowAPI.h"

#include "LowLevelGraphics/Material/Texture/Texture.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"

namespace Atum
{
namespace LowLevelGraphics
{
namespace LowLevelAPI
{

//-----------------------------------------------------------------------------

void Initialize(int *argc, char **argv)
{
    //todo : support more options
    ATUM_ASSERT_MESSAGE(!GetCurrentWindowId(),"Graphic API is already initialized");
    glutInit(argc, argv);

    glutSetOption(GLUT_RENDERING_CONTEXT, GLUT_CREATE_NEW_CONTEXT);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

//-----------------------------------------------------------------------------
void BeginFrame()
{
    ATUM_ASSERT_MESSAGE(GetCurrentWindowId(),"There is no window to render into");

    glutMainLoopEvent();
    ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to begin frame");

    EnableDepthWrite();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DisableDepthWrite();
}

//-----------------------------------------------------------------------------
void EndFrame()
{
    //are there uninitialisation to do here?
    if(GetCurrentWindowId())
    {
        glutSwapBuffers();
        glutPostRedisplay();
    }
    glutLeaveMainLoop();
    ATUM_ASSERT_MESSAGE(!(glGetError()&&GetCurrentWindowId()),"Failed to end frame");
}

void GenerateGeometryBuffer( GeometryGPUParameters& parameters )
{

    ATUM_ASSERT_MESSAGE(parameters.vertexBuffer,"Vertex Buffer must not be null");
    ATUM_ASSERT_MESSAGE(parameters.indexBuffer,"Index Buffer must not be null");

    glGenBuffers(1, &parameters.o_vertexBufID);
    glBindBuffer(GL_ARRAY_BUFFER, parameters.o_vertexBufID);
    glBufferData(GL_ARRAY_BUFFER, 
                    sizeof(glm::vec3)*parameters.vertexBufferSize, 
                    parameters.vertexBuffer, 
                    GL_STATIC_DRAW);
    
    ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate vertex buffer");

   	if (parameters.normalBufferSize > 0)
	{    
        ATUM_ASSERT_MESSAGE(parameters.normalBuffer,"Normal Buffer must not be null"); 
	    glGenBuffers(1, &parameters.o_normalBufID);
	    glBindBuffer(GL_ARRAY_BUFFER, parameters.o_normalBufID);
	    glBufferData(GL_ARRAY_BUFFER, 
                        sizeof(glm::vec3)*parameters.normalBufferSize, 
                        parameters.normalBuffer, 
                        GL_STATIC_DRAW);
        ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate normal buffer");
    }

   	if (parameters.uvBufferSize > 0)
	{ 
        ATUM_ASSERT_MESSAGE(parameters.normalBuffer,"Normal Buffer must not be null"); 
        glGenBuffers(1, &parameters.o_uvBufID);
        glBindBuffer(GL_ARRAY_BUFFER, parameters.o_uvBufID);
        glBufferData(GL_ARRAY_BUFFER, 
                        sizeof(glm::vec2)*parameters.uvBufferSize, 
                        parameters.uvBuffer, 
                        GL_STATIC_DRAW);

        ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate uv buffer");
    }

	if (parameters.skyBoxCoordBufferSize > 0)
	{ 
		ATUM_ASSERT_MESSAGE(parameters.skyBoxCoordBuffer,"Sky Box Coords Buffer must not be null"); 
		glGenBuffers(1, &parameters.o_skyBoxCoordBufID);
		glBindBuffer(GL_ARRAY_BUFFER, parameters.o_skyBoxCoordBufID);
		glBufferData(GL_ARRAY_BUFFER, 
			sizeof(glm::vec3)*parameters.skyBoxCoordBufferSize, 
			parameters.skyBoxCoordBuffer, 
			GL_STATIC_DRAW);

		ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate sky box coords buffer");
	}
    
    if (parameters.colorBufferSize > 0)
    {
        ATUM_ASSERT_MESSAGE(parameters.colorBuffer,"Color Buffer must not be null"); 
        glGenBuffers(1, &parameters.o_colorBufID);
        glBindBuffer(GL_ARRAY_BUFFER, parameters.o_colorBufID);
        glBufferData(
            GL_ARRAY_BUFFER, 
            sizeof(glm::vec4)*parameters.colorBufferSize, 
            parameters.colorBuffer, 
            GL_STATIC_DRAW);

        ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate colorbuffer");
    }

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

    glGenBuffers(1, &parameters.o_indexBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parameters.o_indexBufID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    sizeof(unsigned int)*parameters.indexBufferSize,
                    parameters.indexBuffer,
                    GL_STATIC_DRAW);
	ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to generate index buffer");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//-----------------------------------------------------------------------------
void DeleteGeometryBuffer( unsigned int& vertexBufID, unsigned int& normalBufID, unsigned int& indexBufID, unsigned int& uvBufID )
{
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vertexBufID);
	ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to delete vertex buffer");

    glDeleteBuffers(1, &uvBufID);
    ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to delete uv buffer");

    glDeleteBuffers(1, &normalBufID);
    ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to delete normal buffer");

	glDeleteBuffers(1, &indexBufID);
	ATUM_ASSERT_MESSAGE(!glGetError(),"Failed to delete index buffer");
}

//-----------------------------------------------------------------------------
void GetRenderedData(unsigned char* outputData, int ox, int oy, int width, int height, TextureFormat format)
{
	ATUM_ASSERT_MESSAGE(ox >= 0, "RenderingTarget horizontal origin must be a positive value");
	ATUM_ASSERT_MESSAGE(oy >= 0, "RenderingTarget vertical origin must be a positive value");
	ATUM_ASSERT_MESSAGE(width > 0, "Texture width must greater than 0");
	ATUM_ASSERT_MESSAGE(height > 0, "Texture height must greater than 0");

	glReadPixels(ox, oy, width, height, format, GL_UNSIGNED_BYTE, outputData);
}

//-----------------------------------------------------------------------------
unsigned int GetChannelNumbers(const TextureFormat& tformat)
{
    switch(tformat)
    {
		case ATUM_LUMINANCE:
			return 1;
		case ATUM_RGB:
            return 3;
		case ATUM_RGBA:
			return 4;
        default:
        {
            ATUM_ASSERT_MESSAGE(false, "Texture format is not supported");
            return 0;
        }
    }
}

//-----------------------------------------------------------------------------
void GenerateTexture(unsigned int& textureId, const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const TextureFormat& format)
{
	ATUM_ASSERT_MESSAGE(!imageParameters.imageData.empty(), "Texture data must not be null");
	ATUM_ASSERT_MESSAGE(imageParameters.width > 0, "Texture width must greater than 0");
	ATUM_ASSERT_MESSAGE(imageParameters.height > 0, "Texture height must greater than 0");
	ATUM_ASSERT_MESSAGE(imageParameters.spectrum == GetChannelNumbers(format), "Texture spectrum must greater than 0");

	glGenTextures(1,&textureId);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to generate texture");

	glBindTexture(GL_TEXTURE_2D, textureId);

	gluBuild2DMipmaps( GL_TEXTURE_2D, imageParameters.spectrum, imageParameters.width, imageParameters.height, format, GL_UNSIGNED_BYTE, &imageParameters.imageData[0]);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to load texture");

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to set mipmap filter");
}

//-----------------------------------------------------------------------------
void GenerateTextureSkyBox(unsigned int& textureId, const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const TextureFormat& format)
{
	ATUM_ASSERT_MESSAGE(imageParameters.size() == 6, "It must has 6 textures to generate a sky box");

	std::vector<int> targets;
	targets.reserve(6);
	targets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB);
	targets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB);
	targets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB);
	targets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB);
	targets.push_back(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB);
	targets.push_back(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textureId);

	for(unsigned int cubeSide = 0; cubeSide < 6; ++cubeSide)
	{
		ATUM_ASSERT_MESSAGE(!imageParameters[cubeSide].imageData.empty(), "Texture data must not be null");
		ATUM_ASSERT_MESSAGE(imageParameters[cubeSide].width > 0, "Texture width must greater than 0");
		ATUM_ASSERT_MESSAGE(imageParameters[cubeSide].height > 0, "Texture height must greater than 0");
		ATUM_ASSERT_MESSAGE(imageParameters[cubeSide].spectrum == GetChannelNumbers(format), "Texture spectrum must greater than 0");

		glTexImage2D(targets[cubeSide], 0, format, imageParameters[cubeSide].width, imageParameters[cubeSide].height, 0, format, GL_UNSIGNED_BYTE, &imageParameters[cubeSide].imageData[0]);
		ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to load texture");
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//-----------------------------------------------------------------------------
void DeleteTexture(unsigned int textureId)
{
    glDeleteTextures(1, &textureId);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to delete texture");
}

//-----------------------------------------------------------------------------
void ActivateWireframeMode()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to activate wireframe mode");
}

//-----------------------------------------------------------------------------
void DeactivateWireframeMode()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to deactivate wireframe mode");
}

void DrawBoundingBox( const float* viewMatrix, const float* perspectiveMatrix, const glm::vec3 minCorner, const glm::vec3 maxCorner )
{
	glm::vec3 selectionBoxCorner[8];

	selectionBoxCorner[0] = maxCorner;
	selectionBoxCorner[1] = glm::vec3(maxCorner.x, maxCorner.y, minCorner.z);
	selectionBoxCorner[2] = glm::vec3(maxCorner.x, minCorner.y, minCorner.z);
	selectionBoxCorner[3] = glm::vec3(maxCorner.x, minCorner.y, maxCorner.z);

	selectionBoxCorner[4] = minCorner;
	selectionBoxCorner[5] = glm::vec3(minCorner.x, minCorner.y, maxCorner.z);
	selectionBoxCorner[6] = glm::vec3(minCorner.x, maxCorner.y, maxCorner.z);
	selectionBoxCorner[7] = glm::vec3(minCorner.x, maxCorner.y, minCorner.z);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(viewMatrix);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadMatrixf(perspectiveMatrix);

	glBegin(GL_LINES);

	glColor3f(1,125.0f/255.0f,0); //orange
	//left rectangle
	glVertex3fv(&selectionBoxCorner[0][0]);
	glVertex3fv(&selectionBoxCorner[1][0]);
	glVertex3fv(&selectionBoxCorner[1][0]);
	glVertex3fv(&selectionBoxCorner[2][0]);
	glVertex3fv(&selectionBoxCorner[2][0]);
	glVertex3fv(&selectionBoxCorner[3][0]);
	glVertex3fv(&selectionBoxCorner[3][0]);
	glVertex3fv(&selectionBoxCorner[0][0]);

	//right rectangle
	glVertex3fv(&selectionBoxCorner[4][0]);
	glVertex3fv(&selectionBoxCorner[5][0]);
	glVertex3fv(&selectionBoxCorner[5][0]);
	glVertex3fv(&selectionBoxCorner[6][0]);
	glVertex3fv(&selectionBoxCorner[6][0]);
	glVertex3fv(&selectionBoxCorner[7][0]);
	glVertex3fv(&selectionBoxCorner[7][0]);
	glVertex3fv(&selectionBoxCorner[4][0]);

	//perpendicular lines
	glVertex3fv(&selectionBoxCorner[0][0]);
	glVertex3fv(&selectionBoxCorner[6][0]);
	glVertex3fv(&selectionBoxCorner[1][0]);
	glVertex3fv(&selectionBoxCorner[7][0]);
	glVertex3fv(&selectionBoxCorner[2][0]);
	glVertex3fv(&selectionBoxCorner[4][0]);
	glVertex3fv(&selectionBoxCorner[3][0]);
	glVertex3fv(&selectionBoxCorner[5][0]);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void DrawSphere( const float* modelViewMatrix, const float* perspectiveMatrix )
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(modelViewMatrix);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadMatrixf(perspectiveMatrix);

	glColor3f(0.9,0.9,0.9);
	glutSolidSphere(0.5f,30,30);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

}
}
}
