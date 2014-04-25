#ifndef SCENEMANAGER_GEOMETRY_MANAGER_H
#define SCENEMANAGER_GEOMETRY_MANAGER_H

#include <map>
#include <vector>
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{

namespace LowLevelGraphics
{
	struct GeometryParameters;
	class  Geometry;
}

namespace SceneManager
{

	typedef std::map<GeometryID, LowLevelGraphics::Geometry*> GeometryMap;

	//-----------------------------------------------------------------------------
	class GeometryManager
	{
	public:
		GeometryManager();
		~GeometryManager();

		GeometryID CreateGeometry( const LowLevelGraphics::GeometryParameters& parameters ) ;
		const LowLevelGraphics::Geometry* const GetGeometry( GeometryID geometryID );
		void RemoveGeometry( GeometryID geometryID );
		void ClearAll();

		// Get geometry from id or get id of standard geometry
		GeometryID GetStandardPlaneGeometryId();
		GeometryID GetStandardCubeGeometryId();
		GeometryID GetStandardSphereGeometryId();
		GeometryID GetStandardTorusGeometryId();

	private:
		//void InsertGeometryWithId( LowLevelGraphics::Geometry* const geometry, GeometryID id );
		GeometryID InsertGeometry( LowLevelGraphics::Geometry* const geometry );
		void CreateStandardGeometry();

		GeometryManager(GeometryManager const&);
		void operator=(GeometryManager const&);

	private:
		GeometryMap m_geometryMap;

		GeometryID m_standardPlaneGeometryId;
		GeometryID m_standardCubeGeometryId;
		GeometryID m_standardSphereGeometryId;
		GeometryID m_standardtorusGeometryId;
	};

}
}

#endif