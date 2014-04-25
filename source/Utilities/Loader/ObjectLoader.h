#ifndef UTILITIES_OBJECTLOADER_H
#define UTILITIES_OBJECTLOADER_H

#include <vector>
#include <GLM/include/glm/glm.hpp>
using namespace std;

namespace Atum
{
	namespace Utilities
	{
		namespace ObjectLoader
		{
			/* It returns vertices from triangles of the mesh object 
			please use object file with triangle polygons only */
			/* There are overload methods for loading if certain object files don't have the uv info */
			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec3> & normals, vector<glm::vec2> & uvs);
			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec3> & normals);
			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices, vector<glm::vec2> & uvs);
			bool LoadVisualMeshOBJ(const char * objectPath, vector<glm::vec3> & vertices);
			bool LoadPhysicMeshOBJ(const char * objectPath, vector<glm::vec3> & convexVertices);
		}
	}
}

#endif

