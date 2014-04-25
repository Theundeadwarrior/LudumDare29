#include "PhysicUtilities.h"
#include "Utilities/Physic/Ray.h"

namespace Atum
{
namespace Utilities
{


//Ray-Box intersection courtesy of : http://people.csail.mit.edu/amy/papers/box-jgt.pdf
bool PerformCubeHitTest( const Ray& ray, const glm::vec3& minCorner, const glm::vec3& maxCorner, float& o_interLength )
{
	float TMin, TMax;
	if( ray.GetDirection().x >= 0.0f )
	{
		TMin = (minCorner.x - ray.GetOrigin().x) / ray.GetDirection().x;
		TMax = (maxCorner.x - ray.GetOrigin().x) / ray.GetDirection().x;
	}
	else
	{
		TMin = (maxCorner.x - ray.GetOrigin().x) / ray.GetDirection().x;
		TMax = (minCorner.x - ray.GetOrigin().x) / ray.GetDirection().x;
	}

	float TyMin, TyMax;
	if( ray.GetDirection().y >= 0.0f )
	{
		TyMin = (minCorner.y - ray.GetOrigin().y) / ray.GetDirection().y;
		TyMax = (maxCorner.y - ray.GetOrigin().y) / ray.GetDirection().y;
	}
	else
	{
		TyMin = (maxCorner.y - ray.GetOrigin().y) / ray.GetDirection().y;
		TyMax = (minCorner.y - ray.GetOrigin().y) / ray.GetDirection().y;
	}

	if( (TMin > TyMax) || (TyMin > TMax) )
	{
		return false;
	}

	if (TyMin > TMin) { TMin = TyMin; }
	if (TyMax < TMax) { TMax = TyMax; }

	float TzMin, TzMax;
	if(ray.GetDirection().z >= 0.0f)
	{
		TzMin = (minCorner.z - ray.GetOrigin().z) / ray.GetDirection().z;
		TzMax = (maxCorner.z - ray.GetOrigin().z) / ray.GetDirection().z;
	}
	else
	{
		TzMin = (maxCorner.z - ray.GetOrigin().z) / ray.GetDirection().z;
		TzMax = (minCorner.z - ray.GetOrigin().z) / ray.GetDirection().z;
	}

	if( (TMin > TzMax) || (TzMin > TMax))
	{
		return false;
	}

	if(TzMin > TMin){ TMin = TzMin; }
	if(TzMax < TMax){ TMax = TzMax; }

	if ( TMax > TMin)
	{
		o_interLength = TMin;
		return true;
	}
	else
	{
		return false;
	}
}


// t = [ n . (q - p) ] / (n . v) where 
// n is Plane Normal, q is Plane Origin, v is Ray Direction, p is Ray Origin
bool PerformPlaneHitTest( const Ray& ray, const glm::vec3& planeOrigin, const glm::vec3& planeNormal, float& o_interLength )
{
	float num ( glm::dot(planeNormal, planeOrigin-ray.GetOrigin()) );
	float denum ( glm::dot(planeNormal, ray.GetDirection()) );

	if (denum == 0) //lol
		return false; //the ray is parallel to the plane

	float t ( num/denum );
	if( t < 0 )
		return false; //the ray gets further away from the plane

	o_interLength = t; //it's ok  now!
	return true;
}


}
}