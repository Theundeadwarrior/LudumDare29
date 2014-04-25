#ifndef UTILITIES_BRAINLOADER_H
#define UTILITIES_BRAINLOADER_H

#include <Utilities/BrainLoader/Image3D.h>
#include <LowLevelGraphics/Geometry/Geometry.h>

namespace Atum
{
	namespace Utilities
	{
		namespace BrainLoader
		{
			void CreateBrainGeometry(const char * niftiBrainPath, const float & width, const float & height, 
				const float & depth, const int & skipFactor, LowLevelGraphics::GeometryParameters & geomParam);

			bool LoadNiftiBrain(const char * niftiBrainPath, Image3D & brainImage3D);

			void GenerateCloudPoints(const Image3D & image3D, const float & realWidth, const float & realHeight, 
				const float & realDepth, const unsigned int & skipFactor, vector<glm::vec3> & vertices, 
				vector<glm::vec4> & colors);
		}
	}
}

#endif