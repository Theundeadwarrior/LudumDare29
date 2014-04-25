#ifndef UTILITIES_GEOMETRYGEN_H
#define UTILITIES_GEOMETRYGEN_H

#include "LowLevelGraphics/Geometry/Geometry.h"

namespace Atum
{
namespace Utilities
{
	const float PI = 3.1415926535897932384626433832795f;
	const float TWOPI = 6.283185307179586476925286766559f;
	const float EPSILON = 0.00001f;
	const float D_TO_R = 0.0174532925f;

	LowLevelGraphics::GeometryParameters CreateCubeGeometry(unsigned int length);//counterclockwise
	LowLevelGraphics::GeometryParameters CreateSphereGeometry(float radius, unsigned int slices, unsigned int stacks);
	LowLevelGraphics::GeometryParameters CreatePlaneGeometry(float height, float width);
	LowLevelGraphics::GeometryParameters CreateTorusGeometry(int sides, int cs_sides, float radius, float cs_radius);


	LowLevelGraphics::GeometryParameters CreateSkyBoxGeometry(float sideBox);
}
}


#endif
