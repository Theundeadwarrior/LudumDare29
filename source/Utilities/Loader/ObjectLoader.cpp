#include <Utilities/Loader/ObjectLoader.h>
#include <stdio.h>

namespace Atum
{
	namespace Utilities
	{
		namespace ObjectLoader
		{
			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec3> & normals, vector<glm::vec2> & uvs)
			{
				printf("Loading OBJ file %s...\n", objectPath);

				if (vertices.size() > 0)
					vertices.clear();

				if (normals.size() > 0)
					normals.clear();

				if (uvs.size() > 0)
					uvs.clear();

				vector<unsigned int> vertexIndices, normalIndices, uvIndices;
				vector<glm::vec3> tempVertices; 
				vector<glm::vec2> tempUvs;
				vector<glm::vec3> tempNormals;

				FILE * file;
				if(fopen_s(&file, objectPath, "r") != 0)
				{
					printf("Impossible to open the object file !\n");
					return false;
				}

				while(true)
				{
					char lineHeader[128];

					// Read the first key of the line
					int res = fscanf_s(file, "%s", lineHeader, 128);
					if (res == EOF)
						break;

					if (strcmp(lineHeader, "v") == 0)
					{
						glm::vec3 vertex;
						fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						tempVertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "vt") == 0)
					{
						glm::vec2 uv;
						fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
						tempUvs.push_back(uv);
					}
					else if (strcmp(lineHeader, "vn") == 0)
					{
						glm::vec3 normal;
						fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
						tempNormals.push_back(normal);
					}
					else if (strcmp(lineHeader, "f") == 0)
					{
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
						int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
						if (matches != 9)
						{
							printf("File can't be read by the parser.\n");
							fclose(file);
							return false;
						}

						vertexIndices.push_back(vertexIndex[0]-1);
						vertexIndices.push_back(vertexIndex[1]-1);
						vertexIndices.push_back(vertexIndex[2]-1);
						normalIndices.push_back(normalIndex[0]-1);
						normalIndices.push_back(normalIndex[1]-1);
						normalIndices.push_back(normalIndex[2]-1);
						uvIndices.push_back(uvIndex[0]-1);
						uvIndices.push_back(uvIndex[1]-1);
						uvIndices.push_back(uvIndex[2]-1);
					}
					else
					{
						char buffer[1000];
						fgets(buffer, 1000, file);
					}
				}

				fclose(file);

				// For each vertex of each triangle
				for (unsigned int i=0; i < vertexIndices.size(); i++)
				{
					glm::vec3 vertex = tempVertices[vertexIndices[i]];
					glm::vec3 normal = tempNormals[normalIndices[i]];
					glm::vec2 uv = tempUvs[uvIndices[i]];

					vertices.push_back(vertex);
					normals.push_back(normal);
					uvs.push_back(uv);
				}

				return true;
			}

			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec3> & normals)
			{
				printf("Loading OBJ file %s...\n", objectPath);

				if (vertices.size() > 0)
					vertices.clear();

				if (normals.size() > 0)
					normals.clear();

				vector<unsigned int> vertexIndices, normalIndices;
				vector<glm::vec3> tempVertices; 
				vector<glm::vec3> tempNormals;

				FILE * file;
				if(fopen_s(&file, objectPath, "r") != 0)
				{
					printf("Impossible to open the object file !\n");
					return false;
				}

				while(true)
				{
					char lineHeader[128];

					// Read the first key of the line
					int res = fscanf_s(file, "%s", lineHeader, 128);
					if (res == EOF)
						break;

					if (strcmp(lineHeader, "v") == 0)
					{
						glm::vec3 vertex;
						fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						tempVertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "vn") == 0)
					{
						glm::vec3 normal;
						fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
						tempNormals.push_back(normal);
					}
					else if (strcmp(lineHeader, "f") == 0)
					{
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], normalIndex[3];
						int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
						if (matches != 6)
						{
							printf("File can't be read by the parser.\n");
							fclose(file);
							return false;
						}

						vertexIndices.push_back(vertexIndex[0]-1);
						vertexIndices.push_back(vertexIndex[1]-1);
						vertexIndices.push_back(vertexIndex[2]-1);
						normalIndices.push_back(normalIndex[0]-1);
						normalIndices.push_back(normalIndex[1]-1);
						normalIndices.push_back(normalIndex[2]-1);
					}
					else
					{
						char buffer[1000];
						fgets(buffer, 1000, file);
					}
				}

				fclose(file);

				// For each vertex of each triangle
				for (unsigned int i=0; i < vertexIndices.size(); i++)
				{
					glm::vec3 vertex = tempVertices[vertexIndices[i]];
					glm::vec3 normal = tempNormals[normalIndices[i]];

					vertices.push_back(vertex);
					normals.push_back(normal);
				}

				return true;
			}

			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec2> & uvs)
			{
				printf("Loading OBJ file %s...\n", objectPath);

				if (vertices.size() > 0)
					vertices.clear();

				if (uvs.size() > 0)
					uvs.clear();

				vector<unsigned int> vertexIndices, uvIndices;
				vector<glm::vec3> tempVertices; 
				vector<glm::vec2> tempUvs;

				FILE * file;
				if(fopen_s(&file, objectPath, "r") != 0)
				{
					printf("Impossible to open the object file !\n");
					return false;
				}

				while(true)
				{
					char lineHeader[128];

					// Read the first key of the line
					int res = fscanf_s(file, "%s", lineHeader, 128);
					if (res == EOF)
						break;

					if (strcmp(lineHeader, "v") == 0)
					{
						glm::vec3 vertex;
						fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						tempVertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "vt") == 0)
					{
						glm::vec2 uv;
						fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
						tempUvs.push_back(uv);
					}
					else if (strcmp(lineHeader, "f") == 0)
					{
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3];
						int matches = fscanf_s(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
						if (matches != 6)
						{
							printf("File can't be read by the parser.\n");
							fclose(file);
							return false;
						}

						vertexIndices.push_back(vertexIndex[0]-1);
						vertexIndices.push_back(vertexIndex[1]-1);
						vertexIndices.push_back(vertexIndex[2]-1);
						uvIndices.push_back(uvIndex[0]-1);
						uvIndices.push_back(uvIndex[1]-1);
						uvIndices.push_back(uvIndex[2]-1);
					}
					else
					{
						char buffer[1000];
						fgets(buffer, 1000, file);
					}
				}

				fclose(file);

				// For each vertex of each triangle
				for (unsigned int i=0; i < vertexIndices.size(); i++)
				{
					glm::vec3 vertex = tempVertices[vertexIndices[i]];
					glm::vec2 uv = tempUvs[uvIndices[i]];

					vertices.push_back(vertex);
					uvs.push_back(uv);
				}

				return true;
			}

			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices)
			{
				printf("Loading OBJ file %s...\n", objectPath);

				if (vertices.size() > 0)
					vertices.clear();

				vector<glm::vec3> tempVertices;
				vector<unsigned int> vertexIndices;

				FILE * file;
				if(fopen_s(&file, objectPath, "r") != 0)
				{
					printf("Impossible to open the object file !\n");
					return false;
				}

				while(true)
				{
					char lineHeader[128];

					// Read the first key of the line
					int res = fscanf_s(file, "%s", lineHeader, 128);
					if (res == EOF)
						break;

					if (strcmp(lineHeader, "v") == 0)
					{
						glm::vec3 vertex;
						fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						tempVertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "f") == 0)
					{
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3];
						int matches = fscanf_s(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
						if (matches != 3)
						{
							printf("File can't be read by the parser.\n");
							fclose(file);
							return false;
						}

						vertexIndices.push_back(vertexIndex[0]-1);
						vertexIndices.push_back(vertexIndex[1]-1);
						vertexIndices.push_back(vertexIndex[2]-1);
					}
					else
					{
						char buffer[1000];
						fgets(buffer, 1000, file);
					}
				}

				fclose(file);

				// For each vertex of each triangle
				for (unsigned int i=0; i < vertexIndices.size(); i++)
				{
					glm::vec3 vertex = tempVertices[vertexIndices[i]];

					vertices.push_back(vertex);
				}

				return true;
			}

			// The object file should be shorted to use only the vertex information !
			bool LoadPhysicMeshOBJ(const char * objectPath, vector<glm::vec3> & convexVertices)
			{
				printf("Loading OBJ file %s...\n", objectPath);

				if (convexVertices.size() > 0)
					convexVertices.clear();

				FILE * file;
				if(fopen_s(&file, objectPath, "r") != 0)
				{
					printf("Impossible to open the object file : %s !\n", objectPath);
					return false;
				}

				while(true)
				{
					char lineHeader[128];

					// Read the first key of the line
					int res = fscanf_s(file, "%s", lineHeader, 128);
					if (res == EOF)
						break;

					if (strcmp(lineHeader, "v") == 0)
					{
						glm::vec3 vertex;
						fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						convexVertices.push_back(vertex);
					}
					else
					{
						char buffer[1000];
						fgets(buffer, 1000, file);
					}
				}

				fclose(file);

				return true;
			}
		}
	}

}