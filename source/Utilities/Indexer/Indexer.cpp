#include <Utilities/Indexer/Indexer.h>
#include <Utilities/Debug/Debug.h>
#include <stdio.h>
#include <map>
using namespace std;

namespace Atum
{
	namespace Utilities
	{
		/* Returns the index if the value is in the map */
		bool ContainsValue(VertexUvNormal & vertexUvNormal, map<VertexUvNormal, unsigned int> & vertexUvNormalIndex, unsigned int & result)
		{
				map<VertexUvNormal, unsigned int>::iterator it = vertexUvNormalIndex.find(vertexUvNormal);
				if (it == vertexUvNormalIndex.end())
				{
					return false;
				}
				else
				{
					result = it->second;
					return true;
				}
		}

		void Indexer::IndexVertexUvNormal(const vector<glm::vec3> & vertices, const vector<glm::vec2> & uvs, const vector<glm::vec3> & normals, 
			vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec2> & indexedUvs, vector<glm::vec3> & indexedNormals)
		{
			ATUM_ASSERT_MESSAGE(vertices.size() == normals.size(), "The size of the vertices should be equal to the size of the normals");
			ATUM_ASSERT_MESSAGE(normals.size() == uvs.size(), "The size of the normals should be equal to the size of the uvs");
			if ((vertices.size() != normals.size()) || (normals.size() != uvs.size()))
				return;

			map<VertexUvNormal, unsigned int> vertexUvNormalIndex;

			for (unsigned int i=0; i < vertices.size(); i++)
			{
				VertexUvNormal vertexUvNormal = {vertices[i], uvs[i], normals[i]};

				unsigned int index;

				if (ContainsValue(vertexUvNormal, vertexUvNormalIndex, index))
				{
					indices.push_back(index);
				}
				else
				{
					indexedVertices.push_back(vertices[i]);
					indexedUvs.push_back(uvs[i]);
					indexedNormals.push_back(normals[i]);
					unsigned int newIndex = (unsigned int)indexedVertices.size() - 1;
					indices.push_back(newIndex);
					vertexUvNormalIndex[vertexUvNormal] = newIndex;
				}
			}
		}

		/* Returns the index if the value is in the map */
		bool ContainsValue(VertexNormal & vertexNormal, map<VertexNormal, unsigned int> & vertexNormalIndex, unsigned int & result)
		{
			map<VertexNormal, unsigned int>::iterator it = vertexNormalIndex.find(vertexNormal);
			if (it == vertexNormalIndex.end())
			{
				return false;
			}
			else
			{
				result = it->second;
				return true;
			}
		}

		void Indexer::IndexVertexNormal(const vector<glm::vec3> & vertices, const vector<glm::vec3> & normals, vector<unsigned int> & indices, 
			vector<glm::vec3> & indexedVertices, vector<glm::vec3> & indexedNormals)
		{
			ATUM_ASSERT_MESSAGE(vertices.size() == normals.size(), "The size of the vertices should be equal to the size of the normals");
			if (vertices.size() != normals.size())
				return;

			map<VertexNormal, unsigned int> vertexNormalIndex;

			for (unsigned int i=0; i < vertices.size(); i++ )
			{
				VertexNormal vertexNormal = {vertices[i], normals[i]};

				unsigned int index;
				if (ContainsValue(vertexNormal, vertexNormalIndex, index))
				{
					indices.push_back(index);
				}
				else
				{
					indexedVertices.push_back(vertices[i]);
					indexedNormals.push_back(normals[i]);
					unsigned int newIndex = (unsigned int)indexedVertices.size() - 1;
					indices.push_back(newIndex);
					vertexNormalIndex[vertexNormal] = newIndex;
				}
			}
		}

		/* Returns the index if the value is in the map */
		bool ContainsValue(Vertex & vertex, map<Vertex, unsigned int> & vertexIndex, unsigned int & result)
		{
			map<Vertex, unsigned int>::iterator it = vertexIndex.find(vertex);
			if (it == vertexIndex.end())
			{
				return false;
			}
			else
			{
				result = it->second;
				return true;
			}
		}

		void Indexer::IndexVertex(const vector<glm::vec3> & vertices, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices)
		{
			map<Vertex, unsigned int> vertexIndex;

			for (unsigned int i=0; i < vertices.size(); i++)
			{
				Vertex vertex = {vertices[i]};

				unsigned int index;
				if (ContainsValue(vertex, vertexIndex, index))
				{
					indices.push_back(index);
				}
				else
				{
					indexedVertices.push_back(vertices[i]);
					unsigned int newIndex = (unsigned int)indexedVertices.size() - 1;
					indices.push_back(newIndex);
					vertexIndex[vertex] = newIndex;
				}
			}
		}

		void Indexer::GenerateInterpolatedNormals(const vector<glm::vec3> & vertices, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec3> & indexedNormals)
		{
			ATUM_ASSERT_MESSAGE((vertices.size()%3) == 0, "The size of the vertices should be a multiple of 3");
			if ((vertices.size()%3) != 0)
				return;

			std::vector<glm::vec3> normals;
			// Find the normals
			for (unsigned int i = 0; i < vertices.size(); i+=3)
			{
				glm::vec3 normal = glm::normalize(glm::cross(vertices[i] - vertices[i+1], vertices[i] - vertices[i+2]));
				normals.push_back(normal);
				normals.push_back(normal);
				normals.push_back(normal);
			}

			map<Vertex, unsigned int> vertexIndex;
			map<Vertex, glm::vec3> vertexNormal;

			for(unsigned int i = 0; i < normals.size(); ++i)
			{
				Vertex vertex = {vertices[i]};
				vertexNormal[vertex] += normals[i];
			}

			for(unsigned int i = 0; i < normals.size(); ++i)
			{
				Vertex vertex = {vertices[i]};
				vertexNormal[vertex] = glm::normalize(vertexNormal[vertex]);
			}

			for (unsigned int i=0; i < vertices.size(); i++)
			{
				Vertex vertex = {vertices[i]};

				unsigned int index;
				if (ContainsValue(vertex, vertexIndex, index))
				{
					indices.push_back(index);
				}
				else
				{
					indexedVertices.push_back(vertices[i]);
					unsigned int newIndex = (unsigned int)indexedVertices.size() - 1;
					indices.push_back(newIndex);
					vertexIndex[vertex] = newIndex;
				}
			}

			for (unsigned int i = 0; i < indexedVertices.size(); ++i)
			{
				Vertex vertex = {indexedVertices[i]};
				indexedNormals.push_back(vertexNormal[vertex]);
			}
		}

		/* Returns the index if the value is in the map */
		bool ContainsValue(VertexUv & vertexUv, map<VertexUv, unsigned int> & vertexUvIndex, unsigned int & result)
		{
			map<VertexUv, unsigned int>::iterator it = vertexUvIndex.find(vertexUv);
			if (it == vertexUvIndex.end())
			{
				return false;
			}
			else
			{
				result = it->second;
				return true;
			}
		}

		void Indexer::GenerateInterpolatedNormals(const vector<glm::vec3> & vertices, const vector<glm::vec2> & uvs, vector<unsigned int> & indices, vector<glm::vec3> & indexedVertices, vector<glm::vec2> & indexedUvs, vector<glm::vec3> & indexedNormals)
		{
			ATUM_ASSERT_MESSAGE((vertices.size()%3) == 0, "The size of the vertices should be a multiple of 3");
			if ((vertices.size()%3) != 0)
				return;

			ATUM_ASSERT_MESSAGE(vertices.size() == uvs.size(), "The size of the vertices should be equal to the size of the uvs");
			if (vertices.size() != uvs.size())
				return;

			std::vector<glm::vec3> normals;
			// Find the normals
			for (unsigned int i = 0; i < vertices.size(); i+=3)
			{
				glm::vec3 normal = glm::normalize(glm::cross(vertices[i] - vertices[i+1], vertices[i] - vertices[i+2]));
				normals.push_back(normal);
				normals.push_back(normal);
				normals.push_back(normal);
			}

			map<VertexUv, unsigned int> vertexUvIndex;
			map<Vertex, glm::vec3> vertexNormal;

			for(unsigned int i = 0; i < normals.size(); ++i)
			{
				Vertex vertex = {vertices[i]};
				vertexNormal[vertex] += normals[i];
			}

			for(unsigned int i = 0; i < normals.size(); ++i)
			{
				Vertex vertex = {vertices[i]};
				vertexNormal[vertex] = glm::normalize(vertexNormal[vertex]);
			}

			for (unsigned int i = 0; i < vertices.size(); ++i)
			{
				VertexUv vertexUv = {vertices[i], uvs[i]};

				unsigned int index;
				if (ContainsValue(vertexUv, vertexUvIndex, index))
				{
					indices.push_back(index);
				}
				else
				{
					indexedVertices.push_back(vertices[i]);
					indexedUvs.push_back(uvs[i]);
					unsigned int newIndex = (unsigned int)indexedVertices.size() - 1;
					indices.push_back(newIndex);
					vertexUvIndex[vertexUv] = newIndex;
				}
			}

			for (unsigned int i = 0; i < indexedVertices.size(); ++i)
			{
				Vertex vertex = {indexedVertices[i]};
				indexedNormals.push_back(vertexNormal[vertex]);
			}
		}
	}
}