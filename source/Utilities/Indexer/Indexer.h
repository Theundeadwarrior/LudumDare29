#ifndef UTILITIES_INDEXER_H
#define UTILITIES_INDEXER_H

#include <vector>
#include <GLM/include/glm/glm.hpp>
using namespace std;

namespace Atum
{
	namespace Utilities
	{
		struct VertexUvNormal
		{
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
			bool operator<(const VertexUvNormal that) const
			{
				return memcmp((void*)this, (void*)&that, sizeof(VertexUvNormal)) > 0;
			};
		};

		struct VertexNormal
		{
			glm::vec3 position;
			glm::vec3 normal;
			bool operator<(const VertexNormal that) const
			{
				return memcmp((void*)this, (void*)&that, sizeof(VertexNormal)) > 0;
			};
		};

		struct Vertex
		{
			glm::vec3 position;
			bool operator<(const Vertex that) const
			{
				return memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
			};
		};

		struct VertexUv
		{
			glm::vec3 position;
			glm::vec2 uv;
			bool operator<(const VertexUv that) const
			{
				return memcmp((void*)this, (void*)&that, sizeof(VertexUv)) > 0;
			};
		};

		class Indexer
		{
		public:
			/* This method associates an index for each attribute (vertex, uvs, normal) 
				return values : indices, indexedVertices, indexedUvs, indexedNormals */
			static void IndexVertexUvNormal(const vector<glm::vec3> & vertices, const vector<glm::vec2> & uvs, const vector<glm::vec3> & normals, 
				vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec2> & indexedUvs, vector<glm::vec3> & indexedNormals);
			
			/* This method associates an index for each attribute (vertex, normal) 
				return values : indices, indexedVertices, indexedNormals */
			static void IndexVertexNormal(const vector<glm::vec3> & vertices, const vector<glm::vec3> & normals, 
				vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec3> & indexedNormals);

			/* This method associates an index for each attribute (vertex) 
				return values : indices, indexedVertices */
			static void IndexVertex(const vector<glm::vec3> & vertices, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices);

			/* This method associates an index for each attribute (vertex, normal) 
				return values : indices, indexedVertices and indexedNormals*/
			static void GenerateInterpolatedNormals(const vector<glm::vec3> & vertices, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec3> & indexedNormals);

			/* This method associates an index for each attribute (vertex, uv, normal) 
				return values : indices, indexedVertices, indexedUvs and indexedNormals*/
			static void GenerateInterpolatedNormals(const vector<glm::vec3> & vertices, const vector<glm::vec2> & uvs, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec2> & indexedUvs, vector<glm::vec3> & indexedNormals);
		};
	}
}

#endif

