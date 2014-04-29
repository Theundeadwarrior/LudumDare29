#include "GeometryManager.h"
#include "LowLevelGraphics/Geometry/Geometry.h"

#include "Utilities/IdGenerator/IdGenerator.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"


namespace Atum
{
namespace SceneManager
{

//-----------------------------------------------------------------------------
GeometryManager::GeometryManager()
{
	CreateStandardGeometry();
}

//-----------------------------------------------------------------------------
GeometryManager::~GeometryManager()
{
	GeometryMap::iterator it(m_geometryMap.begin());
	for(; it != m_geometryMap.end(); it++)
	{
		delete (*it).second;
	}
	m_geometryMap.clear();
}

//----------------------------------------------------------------------------
GeometryID GeometryManager::CreateGeometry( const LowLevelGraphics::GeometryParameters& parameters )
{
	LowLevelGraphics::Geometry* geometry = new LowLevelGraphics::Geometry( parameters );
	return InsertGeometry( geometry );
}

//-----------------------------------------------------------------------------
void GeometryManager::CreateStandardGeometry()
{
	m_standardPlaneGeometryId	= CreateGeometry( Utilities::CreatePlaneGeometry(1,1) );
	m_standardCubeGeometryId	= CreateGeometry( Utilities::CreateCubeGeometry(1) );
	m_standardSphereGeometryId	= CreateGeometry( Utilities::CreateSphereGeometry(1,16,16) );
	m_standardtorusGeometryId	= CreateGeometry( Utilities::CreateTorusGeometry(10,40,1,0.5f) );
}

//-----------------------------------------------------------------------------
const LowLevelGraphics::Geometry* const GeometryManager::GetGeometry( GeometryID geometryID )
{
	if ( m_geometryMap.find(geometryID) != m_geometryMap.end() ) //id exists!
	{
		return m_geometryMap[geometryID];
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
GeometryID GeometryManager::GetStandardPlaneGeometryId()
{
	return m_standardPlaneGeometryId;
}

//-----------------------------------------------------------------------------
GeometryID GeometryManager::GetStandardCubeGeometryId()
{
	return m_standardCubeGeometryId;
}

//-----------------------------------------------------------------------------
GeometryID GeometryManager::GetStandardSphereGeometryId()
{
	return m_standardSphereGeometryId;
}

//-----------------------------------------------------------------------------
GeometryID GeometryManager::GetStandardTorusGeometryId()
{
	return m_standardtorusGeometryId;
}

//-----------------------------------------------------------------------------
GeometryID GeometryManager::InsertGeometry( LowLevelGraphics::Geometry* const geometry )
{
	unsigned long int id = Utilities::IdGenerator::GetInstance().GenerateId();
	m_geometryMap[id] = geometry;
	return id;
}

//-----------------------------------------------------------------------------
void GeometryManager::RemoveGeometry( GeometryID geometryID )
{
	GeometryMap::iterator it ( m_geometryMap.find(geometryID) );
	if ( it != m_geometryMap.end() ) //id exists!
	{
		delete (*it).second;
		m_geometryMap.erase(it);
	}
}

//-----------------------------------------------------------------------------
void GeometryManager::ClearAll()
{
	GeometryMap::iterator it(m_geometryMap.begin());
	for(; it != m_geometryMap.end(); it++)
	{
		delete (*it).second;
	}
	m_geometryMap.clear();
	CreateStandardGeometry();
}


/*void GeometryManager::InsertGeometryWithId( LowLevelGraphics::Geometry* const geometry, GeometryID id )
{
	m_geometryMap[id] = geometry;
}*/

}
}