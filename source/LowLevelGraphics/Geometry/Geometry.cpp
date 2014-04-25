#include "Geometry.h"
#include "Utilities/BasicGeometry/BasicGeometryGenerator.h"
#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace LowLevelGraphics
{

Geometry::Geometry( const GeometryParameters& parameters )
{
	ATUM_ASSERT( parameters.position.size() != 0 );
	//ATUM_ASSERT( parameters.index.size() != 0 );

	//to remove eventually
	m_vertex = parameters.position;
	m_normal = parameters.normal;
	m_index = parameters.index;
	m_textureCoordinates = parameters.textureCoordinates;
	m_skyBoxCoords = parameters.skyBoxCoords;
	m_color = parameters.color;

	GeometryGPUParameters GPUparameters;

	GPUparameters.vertexBuffer	= &m_vertex[0];
	//GPUparameters.indexBuffer	= &m_index[0];

	if ( m_index.size() != 0 )
		GPUparameters.indexBuffer	= &m_index[0];
	else
		GPUparameters.indexBuffer	= 0;

	if ( m_normal.size() != 0 )
		GPUparameters.normalBuffer	= &m_normal[0];
	else
		GPUparameters.normalBuffer	= 0;

	if ( m_textureCoordinates.size() != 0 )
		GPUparameters.uvBuffer	= &m_textureCoordinates[0];
	else
		GPUparameters.uvBuffer	= 0;

	if ( m_skyBoxCoords.size() != 0 )
		GPUparameters.skyBoxCoordBuffer	= &m_skyBoxCoords[0];
	else
		GPUparameters.skyBoxCoordBuffer	= 0;

	if ( m_color.size() != 0 )
		GPUparameters.colorBuffer	= &m_color[0];
	else
		GPUparameters.colorBuffer	= 0;

	GPUparameters.vertexBufferSize	= GetVertexBufferSize();
	GPUparameters.normalBufferSize	= GetNormalBufferSize();
	GPUparameters.indexBufferSize	= GetIndexBufferSize();
	GPUparameters.uvBufferSize		= GetUVBufferSize();
	GPUparameters.skyBoxCoordBufferSize	= GetSkyBoxCoordBufferSize();
	GPUparameters.colorBufferSize	= GetColorBufferSize();

	GPUparameters.o_indexBufID = GPUparameters.o_normalBufID = GPUparameters.o_uvBufID = GPUparameters.o_skyBoxCoordBufID = GPUparameters.o_vertexBufID = GPUparameters.o_colorBufID = 0;

	//Call the GPU to store the geometry
	LowLevelGraphics::LowLevelAPI::GenerateGeometryBuffer( GPUparameters );

	//Store the IDs
	m_vertexID	= GPUparameters.o_vertexBufID;
	m_normalID	= GPUparameters.o_normalBufID;
	m_indexID	= GPUparameters.o_indexBufID;
	m_uvID		= GPUparameters.o_uvBufID;
	m_skyBoxCoordID = GPUparameters.o_skyBoxCoordBufID;
	m_colorID	= GPUparameters.o_colorBufID;

        //Calculate OBB
	m_obb.UpdateBoundingBox(parameters.position);
}

Geometry::~Geometry()
{
	LowLevelGraphics::LowLevelAPI::DeleteGeometryBuffer( m_vertexID, m_normalID, m_indexID, m_uvID );
}

} // namespace LowLevelGraphics
} // namespace Atum