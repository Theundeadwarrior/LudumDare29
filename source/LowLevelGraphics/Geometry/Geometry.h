#ifndef LOWLEVELGRAPHICS_GEOMETRY_H
#define LOWLEVELGRAPHICS_GEOMETRY_H

#include <vector>
#include <map>
#include "GLM/include/glm/glm.hpp"

#include "Utilities/Physic/OBB.h"

namespace Atum
{

namespace SceneManager
{
	class GeometryManager;
}

namespace LowLevelGraphics
{
	//-----------------------------------------------------------------------------
	struct GeometryParameters
	{
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> normal;
		std::vector<unsigned int> index;	
		std::vector<glm::vec2> textureCoordinates;
		std::vector<glm::vec3> skyBoxCoords;
		std::vector<glm::vec4> color;
	};

	//-----------------------------------------------------------------------------
	class Geometry
	{
		friend class SceneManager::GeometryManager;

		public:
			~Geometry();
			unsigned int GetVertexBufferID() const	{ return m_vertexID; }
			unsigned int GetNormalBufferID() const	{ return m_normalID; }
			unsigned int GetIndexBufferID() const	{ return m_indexID; }
			unsigned int GetUVBufferID() const		{ return m_uvID; }
			unsigned int GetSkyBoxCoordBufferID() const		{ return m_skyBoxCoordID; }
			unsigned int GetColorBufferID() const	{ return m_colorID; }

			unsigned int GetVertexBufferSize() const	{ return m_vertex.size(); }
			unsigned int GetNormalBufferSize() const	{ return m_normal.size(); }
			unsigned int GetIndexBufferSize() const		{ return m_index.size(); }
			unsigned int GetUVBufferSize() const		{ return m_textureCoordinates.size(); }
			unsigned int GetSkyBoxCoordBufferSize() const		{ return m_skyBoxCoords.size(); }
			unsigned int GetColorBufferSize() const		{ return m_color.size(); }

			const Utilities::OBB* const GetOBB() const { return &m_obb; }

			std::vector<glm::vec3> m_vertex; // to delete
			std::vector<glm::vec3> m_normal; //to delete
			std::vector<unsigned int> m_index; //to delete	
			std::vector<glm::vec2> m_textureCoordinates; //to delete
			std::vector<glm::vec3> m_skyBoxCoords; //to delete
			std::vector<glm::vec4> m_color; // to delete

		private:
			Geometry( const GeometryParameters& parameters );

			unsigned int m_vertexID;
			unsigned int m_normalID;
			unsigned int m_indexID;
			unsigned int m_uvID;
			unsigned int m_skyBoxCoordID;
			unsigned int m_colorID;

	                Utilities::OBB m_obb;
	};

	//---------------------------------------------------------------------------
	struct GeometryGPUParameters
	{
		const glm::vec3* vertexBuffer;
		const glm::vec3* normalBuffer;
		const unsigned int* indexBuffer;
		const glm::vec2* uvBuffer;
		const glm::vec3* skyBoxCoordBuffer;
		const glm::vec4* colorBuffer;

		unsigned int vertexBufferSize;
		unsigned int normalBufferSize; 
		unsigned int indexBufferSize; 
		unsigned int uvBufferSize;
		unsigned int skyBoxCoordBufferSize;
		unsigned int colorBufferSize;

		unsigned int o_vertexBufID;
		unsigned int o_normalBufID; 
		unsigned int o_indexBufID; 
		unsigned int o_uvBufID;
		unsigned int o_skyBoxCoordBufID;
		unsigned int o_colorBufID;
	};


} // namespace LowLevelGraphics
} // namespace Atum

#endif
