#ifndef LOWLEVELGRAPHICS_LOWLEVELAPI_GPUAPI_LOWLEVELGPUAPI_H
#define LOWLEVELGRAPHICS_LOWLEVELAPI_GPUAPI_LOWLEVELGPUAPI_H

#include "glew/include/GL/glew.h"
#include "freeglut/include/GL/freeglut.h"
#include "Utilities/Image/ImageUtilities.h"
#include "LowLevelGraphics/Geometry/Geometry.h"
#include "ParticleSystem/ParticleSystem.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace LowLevelGraphics
{

namespace LowLevelAPI
{

enum TextureFormat
{
	ATUM_LUMINANCE = GL_LUMINANCE,
    ATUM_RGB = GL_RGB,
	ATUM_RGBA = GL_RGBA
};

void Initialize(int *argc, char **argv);
void BeginFrame();
void EndFrame();

void GenerateTexture(unsigned int& textureId, const Utilities::Image::ImageParameters<unsigned char>& imageParameters, const TextureFormat& format);
void GenerateTextureSkyBox(unsigned int& textureId, const std::vector<Utilities::Image::ImageParameters<unsigned char>>& imageParameters, const TextureFormat& format);
void DeleteTexture(unsigned int textureId);

void GenerateGeometryBuffer( GeometryGPUParameters& parameters );
void DeleteGeometryBuffer( unsigned int& vertexBufID, unsigned int& normalBufID, unsigned int& indexBufID, unsigned int& uvBufID );

void DrawCall(const Geometry* const geometry, unsigned int shaderProgramId);
void DrawCallParticles(const std::vector<ParticleSystem::Particle>& particles);
void DrawCallPointCloud(const Geometry* const geometry, unsigned int shaderProgramId);
void DrawSkyBox(const Geometry* const geometry, unsigned int shaderProgramId);

void GetRenderedData(unsigned char* outputData, int ox, int oy, int width, int height, TextureFormat format);

void EnableDepthRead();
void DisableDepthRead();
void EnableDepthWrite();
void DisableDepthWrite();
void EnableBackFaceCulling();
void DisableBackFaceCulling();
void EnableAlphaBlending();
void DisableAlphaBlending();
void SetAlphaBlendFunc();
void SetAdditiveBlendFunc();

void ActivateWireframeMode();
void DeactivateWireframeMode();

void DrawBoundingBox(
	const float* viewMatrix, 
	const float* perspectiveMatrix, 
	const glm::vec3 minCorner, 
	const glm::vec3 maxCorner);

void DrawSphere(
	const float* modelViewMatrix, 
	const float* perspectiveMatrix);

//-------------------------------
inline void DrawCall(const Geometry* const geometry, unsigned int shaderProgramId)
{ 
    ATUM_ASSERT_MESSAGE(geometry,"Geometry buffer must not be null");

	int vertexLoc = glGetAttribLocation(shaderProgramId,"position");
	int normalLoc = glGetAttribLocation(shaderProgramId,"normal");
	int texCoordsLoc = glGetAttribLocation(shaderProgramId,"texCoords");

	glEnableVertexAttribArray(vertexLoc);
	glEnableVertexAttribArray(normalLoc);
	glEnableVertexAttribArray(texCoordsLoc);

    glBindBuffer(GL_ARRAY_BUFFER, geometry->GetVertexBufferID());
	glVertexAttribPointer(vertexLoc , 3, GL_FLOAT, 0, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->GetUVBufferID());
	glVertexAttribPointer(texCoordsLoc , 2, GL_FLOAT, 0, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->GetNormalBufferID());
	glVertexAttribPointer(normalLoc , 3, GL_FLOAT, 0, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->GetIndexBufferID());



    glDrawElements(GL_TRIANGLES, geometry->GetIndexBufferSize(), GL_UNSIGNED_INT, 0);
	GLenum error = glGetError();
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to draw elements");

	glDisableVertexAttribArray(vertexLoc);
	glDisableVertexAttribArray(normalLoc);
	glDisableVertexAttribArray(texCoordsLoc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// There is an error if we don't have a texture in use. We are trying to update the text coords but they are not
	// present in the shader because of the ifdef system. We should have a check if we have a texture and feed the
	// params to the shader only if we do. If we don't catch the error, the next glGetError() could be erronous.
	glGetError();

}

inline void DrawCallParticles(const std::vector<ParticleSystem::Particle>& particles)
{
	glBegin(GL_POINTS);
	{
		for(unsigned int i = 0; i < particles.size(); ++i)
		{
			if(particles[i].IsAlive())
			{
				glVertex3f(particles[i].GetPosition().x,particles[i].GetPosition().y,particles[i].GetPosition().z);
			}	
		}
	}
	glEnd();
}

inline void DrawCallPointCloud(const Geometry* const geometry, unsigned int shaderProgramId)
{ 
    ATUM_ASSERT_MESSAGE(geometry,"Geometry buffer must not be null");

	int vertexLoc = glGetAttribLocation(shaderProgramId,"position");
	int colorLoc = glGetAttribLocation(shaderProgramId,"color");

	glEnableVertexAttribArray(vertexLoc);
	glEnableVertexAttribArray(colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->GetVertexBufferID());
	glVertexAttribPointer(vertexLoc , 3, GL_FLOAT, 0, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->GetColorBufferID());
	glVertexAttribPointer(colorLoc ,4, GL_FLOAT, 0, 0, 0);

	glDrawArrays(GL_POINTS, 0, geometry->GetVertexBufferSize());
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to draw point cloud");

	glDisableVertexAttribArray(vertexLoc);
	glDisableVertexAttribArray(colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//-------------------------------
inline void DrawSkyBox(const Geometry* const geometry, unsigned int shaderProgramId)
{ 
	int vertexLoc = glGetAttribLocation(shaderProgramId,"position");
	int coordCubeLoc = glGetAttribLocation(shaderProgramId,"coordCube");

	glEnableVertexAttribArray(vertexLoc);
	glEnableVertexAttribArray(coordCubeLoc);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->GetVertexBufferID());
	glVertexAttribPointer(vertexLoc , 3, GL_FLOAT, 0, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->GetSkyBoxCoordBufferID());
	glVertexAttribPointer(coordCubeLoc ,3, GL_FLOAT, 0, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
	glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to draw sky box");

	glDisableVertexAttribArray(vertexLoc);
	glDisableVertexAttribArray(coordCubeLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//-------------------------------
inline void EnableDepthRead()
{
    glEnable(GL_DEPTH_TEST);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to enable depth buffer reading");
}

//-------------------------------
inline void DisableDepthRead()
{
    glDisable(GL_DEPTH_TEST);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to disable depth buffer reading");
}

//-------------------------------
inline void EnableDepthWrite()
{
    glDepthMask(GL_TRUE);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to enable depth buffer writing");
}

//-------------------------------
inline void DisableDepthWrite()
{
    glDepthMask(GL_FALSE);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to disable depth buffer writing");
}

//-------------------------------
inline void EnableBackFaceCulling()
{
    glEnable(GL_CULL_FACE);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to enable back-face culling");
}

//-------------------------------
inline void DisableBackFaceCulling()
{
    glDisable(GL_CULL_FACE);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to disable back-face culling");
}

//-------------------------------
inline void EnableTextureCubeMap()
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to enable texture cube map");
}

//-------------------------------
inline void DisableTextureCubeMap()
{
	glDisable(GL_TEXTURE_CUBE_MAP);
	ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to disable texture cube map");
}

//-------------------------------
inline void EnableAlphaBlending()
{
    glEnable(GL_BLEND);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to enable alpha blending");
}

//-------------------------------
inline void DisableAlphaBlending()
{
    glDisable(GL_BLEND);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to disable alpha blending");
}

//-------------------------------
inline void SetAlphaBlendFunc()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//-------------------------------
inline void SetAdditiveBlendFunc()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

}
}
}
#endif
