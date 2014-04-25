#ifndef UNITTEST_INDEXERUNITTESTS_H
#define UNITTEST_INDEXERUNITTESTS_H
#include <gtest/gtest.h>
#include <GLM/include/glm/glm.hpp> 
#include <Utilities/Loader/ObjectLoader.h>
#include <Utilities/Indexer/Indexer.h>

namespace Atum
{
	namespace UnitTest
	{
		class IndexerUnitTests : public testing::Test {
		protected:
			// You can remove any or all of the following functions if its body
			// is empty.
			IndexerUnitTests()
			{
				// You can do set-up work for each test here.
				// The test geometry here is a pyramid
				vector<glm::vec3> pyramidBase;
				glm::vec3 pyramidTop = glm::vec3(0,1,0);
				pyramidBase.push_back(glm::vec3(0,0,1));
				pyramidBase.push_back(glm::vec3(1,0,0));
				pyramidBase.push_back(glm::vec3(0,0,-1));
				pyramidBase.push_back(glm::vec3(-1,0,0));

				m_vertices.push_back(pyramidBase[1]);
				m_vertices.push_back(pyramidTop);
				m_vertices.push_back(pyramidBase[0]);

				m_vertices.push_back(pyramidBase[2]);
				m_vertices.push_back(pyramidTop);
				m_vertices.push_back(pyramidBase[1]);

				m_vertices.push_back(pyramidBase[3]);
				m_vertices.push_back(pyramidTop);
				m_vertices.push_back(pyramidBase[2]);

				m_vertices.push_back(pyramidBase[0]);
				m_vertices.push_back(pyramidTop);
				m_vertices.push_back(pyramidBase[3]);

				// Find the normals and uvs
				vector<glm::vec2> uvs;
				uvs.push_back(glm::vec2(0.0f,0.0f));
				uvs.push_back(glm::vec2(0.0f,1.0f));
				uvs.push_back(glm::vec2(1.0f,1.0f));
				for (unsigned int i = 0; i < m_vertices.size(); i+=3)
				{
					glm::vec3 normal = glm::normalize(glm::cross(m_vertices[i] - m_vertices[i+1], m_vertices[i] - m_vertices[i+2]));
					m_normals.push_back(normal);
					m_normals.push_back(normal);
					m_normals.push_back(normal);
					m_uvs.push_back(uvs[0]);
					m_uvs.push_back(uvs[1]);
					m_uvs.push_back(uvs[2]);

					m_invalidNormals.push_back(normal);
					m_invalidNormals.push_back(normal);
					m_invalidUvs.push_back(glm::vec2(0,0));
				}

				m_invalidVertices.push_back(pyramidBase[1]);
				m_invalidVertices.push_back(pyramidTop);

				m_invalidVertices.push_back(pyramidBase[2]);
				m_invalidVertices.push_back(pyramidTop);
				m_invalidVertices.push_back(pyramidBase[1]);

				m_invalidVertices.push_back(pyramidBase[3]);
				m_invalidVertices.push_back(pyramidTop);

				m_invalidVertices.push_back(pyramidBase[0]);
				m_invalidVertices.push_back(pyramidTop);
				m_invalidVertices.push_back(pyramidBase[3]);
			}

			virtual ~IndexerUnitTests()
			{
				// You can do clean-up work that doesn't throw exceptions here.

			}

			// If the constructor and destructor are not enough for setting up
			// and cleaning up each test, you can define the following methods:
			virtual void SetUp()
			{
				// Code here will be called immediately after the constructor (right
				// before each test).
			}

			virtual void TearDown()
			{
				// Code here will be called immediately after each test (right
				// before the destructor).
			}

			vector<glm::vec3> m_vertices;
			vector<glm::vec3> m_normals;
			vector<glm::vec2> m_uvs;

			vector<glm::vec3> m_invalidVertices; // here we don't have a good number of triangles
			vector<glm::vec3> m_invalidNormals; // not the same size as the vertices
			vector<glm::vec2> m_invalidUvs; // not the same size as the vertices
		};


		// Test the success of functions of the index utility
		TEST_F(IndexerUnitTests, TestGenerateInterpolateNormals)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			Utilities::Indexer::GenerateInterpolatedNormals(m_vertices, indices, indexedVertices, indexedNormals);
			EXPECT_EQ(indices.size(), 12);
			EXPECT_EQ(indexedVertices.size(), 5);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());

			vector<glm::vec3> expectedIndexedNormals;
			expectedIndexedNormals.push_back(glm::vec3(0.70710683,0.70710683,0));
			expectedIndexedNormals.push_back(glm::vec3(0,1,0));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,-0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(-0.70710683,0.70710683,0));
			EXPECT_EQ(indexedNormals, expectedIndexedNormals);

			vector<glm::vec3> expectedIndexedVertices;
			expectedIndexedVertices.push_back(glm::vec3(1,0,0));
			expectedIndexedVertices.push_back(glm::vec3(0,1,0));
			expectedIndexedVertices.push_back(glm::vec3(0,0,1));
			expectedIndexedVertices.push_back(glm::vec3(0,0,-1));
			expectedIndexedVertices.push_back(glm::vec3(-1,0,0));
			EXPECT_EQ(indexedVertices, expectedIndexedVertices);

			vector<unsigned int> expectedIndices;
			expectedIndices.push_back(0);expectedIndices.push_back(1);expectedIndices.push_back(2);
			expectedIndices.push_back(3);expectedIndices.push_back(1);expectedIndices.push_back(0);
			expectedIndices.push_back(4);expectedIndices.push_back(1);expectedIndices.push_back(3);
			expectedIndices.push_back(2);expectedIndices.push_back(1);expectedIndices.push_back(4);
			EXPECT_EQ(indices, expectedIndices);
		}

		TEST_F(IndexerUnitTests, TestGenerateInterpolateNormals02)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			vector<glm::vec2> indexedUvs;
			Utilities::Indexer::GenerateInterpolatedNormals(m_vertices, m_uvs, indices, indexedVertices, indexedUvs, indexedNormals);
			EXPECT_EQ(indices.size(), 12);
			EXPECT_EQ(indexedVertices.size(), 9);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
			EXPECT_EQ(indexedNormals.size(), indexedUvs.size());

			vector<glm::vec3> expectedIndexedNormals;
			expectedIndexedNormals.push_back(glm::vec3(0.70710683,0.70710683,0));
			expectedIndexedNormals.push_back(glm::vec3(0,1,0));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,-0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(0.70710683,0.70710683,0));
			expectedIndexedNormals.push_back(glm::vec3(-0.70710683,0.70710683,0));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,-0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(0,0.70710683,0.70710683));
			expectedIndexedNormals.push_back(glm::vec3(-0.70710683,0.70710683,0));
			EXPECT_EQ(indexedNormals, expectedIndexedNormals);

			vector<glm::vec3> expectedIndexedVertices;
			expectedIndexedVertices.push_back(glm::vec3(1,0,0));
			expectedIndexedVertices.push_back(glm::vec3(0,1,0));
			expectedIndexedVertices.push_back(glm::vec3(0,0,1));
			expectedIndexedVertices.push_back(glm::vec3(0,0,-1));
			expectedIndexedVertices.push_back(glm::vec3(1,0,0));
			expectedIndexedVertices.push_back(glm::vec3(-1,0,0));
			expectedIndexedVertices.push_back(glm::vec3(0,0,-1));
			expectedIndexedVertices.push_back(glm::vec3(0,0,1));
			expectedIndexedVertices.push_back(glm::vec3(-1,0,0));
			EXPECT_EQ(indexedVertices, expectedIndexedVertices);

			vector<unsigned int> expectedIndices;
			expectedIndices.push_back(0);expectedIndices.push_back(1);expectedIndices.push_back(2);
			expectedIndices.push_back(3);expectedIndices.push_back(1);expectedIndices.push_back(4);
			expectedIndices.push_back(5);expectedIndices.push_back(1);expectedIndices.push_back(6);
			expectedIndices.push_back(7);expectedIndices.push_back(1);expectedIndices.push_back(8);
			EXPECT_EQ(indices, expectedIndices);
		}

		TEST_F(IndexerUnitTests, TestIndexVertex)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			Utilities::Indexer::IndexVertex(m_vertices, indices, indexedVertices);
			EXPECT_EQ(indices.size(), 12);
			EXPECT_EQ(indexedVertices.size(), 5);

			vector<glm::vec3> expectedIndexedVertices;
			expectedIndexedVertices.push_back(glm::vec3(1,0,0));
			expectedIndexedVertices.push_back(glm::vec3(0,1,0));
			expectedIndexedVertices.push_back(glm::vec3(0,0,1));
			expectedIndexedVertices.push_back(glm::vec3(0,0,-1));
			expectedIndexedVertices.push_back(glm::vec3(-1,0,0));
			EXPECT_EQ(indexedVertices, expectedIndexedVertices);

			vector<unsigned int> expectedIndices;
			expectedIndices.push_back(0);expectedIndices.push_back(1);expectedIndices.push_back(2);
			expectedIndices.push_back(3);expectedIndices.push_back(1);expectedIndices.push_back(0);
			expectedIndices.push_back(4);expectedIndices.push_back(1);expectedIndices.push_back(3);
			expectedIndices.push_back(2);expectedIndices.push_back(1);expectedIndices.push_back(4);
			EXPECT_EQ(indices, expectedIndices);
		}

		TEST_F(IndexerUnitTests, TestIndexVertexNormal)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			Utilities::Indexer::IndexVertexNormal(m_vertices, m_normals, indices, indexedVertices, indexedNormals);
			EXPECT_EQ(indices.size(), 12);
			EXPECT_EQ(indexedVertices.size(), 12);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());

			EXPECT_EQ(indexedVertices, m_vertices);
			EXPECT_EQ(indexedNormals, m_normals);

			vector<unsigned int> expectedIndices;
			expectedIndices.push_back(0);expectedIndices.push_back(1);expectedIndices.push_back(2);
			expectedIndices.push_back(3);expectedIndices.push_back(4);expectedIndices.push_back(5);
			expectedIndices.push_back(6);expectedIndices.push_back(7);expectedIndices.push_back(8);
			expectedIndices.push_back(9);expectedIndices.push_back(10);expectedIndices.push_back(11);
			EXPECT_EQ(indices, expectedIndices);
		}

		TEST_F(IndexerUnitTests, TestIndexVertexUvNormal)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			vector<glm::vec2> indexedUvs;
			Utilities::Indexer::IndexVertexUvNormal(m_vertices, m_uvs, m_normals, indices, indexedVertices, indexedUvs, indexedNormals);
			EXPECT_EQ(indices.size(), 12);
			EXPECT_EQ(indexedVertices.size(), 12);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
			EXPECT_EQ(indexedVertices.size(), indexedUvs.size());

			EXPECT_EQ(indexedVertices, m_vertices);
			EXPECT_EQ(indexedNormals, m_normals);
			EXPECT_EQ(indexedUvs, m_uvs);

			vector<unsigned int> expectedIndices;
			expectedIndices.push_back(0);expectedIndices.push_back(1);expectedIndices.push_back(2);
			expectedIndices.push_back(3);expectedIndices.push_back(4);expectedIndices.push_back(5);
			expectedIndices.push_back(6);expectedIndices.push_back(7);expectedIndices.push_back(8);
			expectedIndices.push_back(9);expectedIndices.push_back(10);expectedIndices.push_back(11);
			EXPECT_EQ(indices, expectedIndices);
		}

		// Test functions with invalid parameters
		TEST_F(IndexerUnitTests, TestFailureIndexVertexNormal)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			Utilities::Indexer::IndexVertexNormal(m_vertices, m_invalidNormals, indices, indexedVertices, indexedNormals);
			EXPECT_EQ(indices.size(), 0);
			EXPECT_EQ(indexedVertices.size(), 0);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
		}

		TEST_F(IndexerUnitTests, TestFailureIndexVertexUvNormal)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			vector<glm::vec2> indexedUvs;
			Utilities::Indexer::IndexVertexUvNormal(m_vertices, m_invalidUvs, m_invalidNormals, indices, indexedVertices, indexedUvs, indexedNormals);
			EXPECT_EQ(indices.size(), 0);
			EXPECT_EQ(indexedVertices.size(), 0);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
			EXPECT_EQ(indexedUvs.size(), indexedVertices.size());
		}

		// When the size of vertices is not a multiple of 3
		TEST_F(IndexerUnitTests, TestFailureGenerateInterpolateNormals)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			Utilities::Indexer::GenerateInterpolatedNormals(m_invalidVertices, indices, indexedVertices, indexedNormals);
			EXPECT_EQ(indices.size(), 0);
			EXPECT_EQ(indexedVertices.size(), 0);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
		}

		TEST_F(IndexerUnitTests, TestFailureGenerateInterpolateNormals02)
		{
			vector<unsigned int> indices;
			vector<glm::vec3> indexedVertices;
			vector<glm::vec3> indexedNormals;
			vector<glm::vec2> indexedUvs;
			Utilities::Indexer::GenerateInterpolatedNormals(m_invalidVertices, m_invalidUvs, indices, indexedVertices, indexedUvs, indexedNormals);
			EXPECT_EQ(indices.size(), 0);
			EXPECT_EQ(indexedVertices.size(), 0);
			EXPECT_EQ(indexedNormals.size(), indexedVertices.size());
			EXPECT_EQ(indexedUvs.size(), indexedVertices.size());
		}
	}
}

#endif