#include <vector>
#include "BasicGeometryGenerator.h"
#include "Utilities/Debug/Debug.h"
#include "Utilities/Indexer/Indexer.h"

namespace Atum
{
namespace Utilities
{

LowLevelGraphics::GeometryParameters Utilities::CreatePlaneGeometry(float height, float width)
{
	LowLevelGraphics::GeometryParameters geom;

	std::vector<glm::vec3> vertices;
	glm::vec3 vertex;

	float halfHeight = height/2.0f;
    float halfWidth = width/2.0f;

	vertex.x = -halfWidth;
	vertex.y = halfHeight;
	vertex.z = 0.0f;
	vertices.push_back(vertex);

	vertex.x = -halfWidth;
	vertex.y = -halfHeight;
	vertices.push_back(vertex);

	vertex.x = halfWidth;
	vertex.y = -halfHeight;
	vertices.push_back(vertex);

	vertex.x = -halfWidth;
	vertex.y = halfHeight;
	vertices.push_back(vertex);

	vertex.x = halfWidth;
	vertex.y = -halfHeight;
	vertices.push_back(vertex);

	vertex.x = halfWidth;
	vertex.y = halfHeight;
	vertices.push_back(vertex);

	std::vector<glm::vec3> normals;
	glm::vec3 normal;
	normal.x = 0.0f;
	normal.y = 0.0f;
	normal.z = -1.0f;
	for(int i=0; i<6; i++)
	{
		normals.push_back(normal);
	}

	std::vector<glm::vec2> uvs;
	uvs.push_back(glm::vec2(0,0));
	uvs.push_back(glm::vec2(1,0));
	uvs.push_back(glm::vec2(1,1));
	uvs.push_back(glm::vec2(0,0));
	uvs.push_back(glm::vec2(1,1));
	uvs.push_back(glm::vec2(0,1));

	Utilities::Indexer::IndexVertexUvNormal(vertices, uvs, normals, geom.index, geom.position, geom.textureCoordinates, geom.normal);

	return geom;
}

LowLevelGraphics::GeometryParameters Utilities::CreateTorusGeometry(int sides, int cs_sides, float radius, float cs_radius)
{
	LowLevelGraphics::GeometryParameters geom;
	std::vector<glm::vec3> vertices;
	glm::vec3 vertex;
	std::vector<glm::vec3> normals;

	int angleincs = 360/sides;
	int cs_angleincs = 360/cs_sides;
	float currentradius, zval;

	//calculating the vertex array
	for (int j=0; j<360; j+=cs_angleincs)
	{
		currentradius = radius + (cs_radius * cosf(j * D_TO_R ));
		zval = cs_radius * sinf(j * D_TO_R );

		for (int i=0; i<360; i+=angleincs)
		{
			//Calculate vertex
			vertex.x = currentradius * cosf(i * D_TO_R ); // x 
			vertex.y = currentradius * sinf(i * D_TO_R ); // y
			vertex.z = zval;                              // z
			vertices.push_back(vertex);

			//Calculate normal
			float tx, ty, tz, sx, sy, sz, length;
			glm::vec3 normal;

			tx = -sinf(i * D_TO_R);
			ty = cosf(i * D_TO_R);
			tz = 0;

			sx = cosf(i*D_TO_R)*(-sinf(j*D_TO_R));
			sy = sinf(i*D_TO_R)*(-sinf(j*D_TO_R));
			sz = cosf(j*D_TO_R);

			normal.x = ty*sz - tz*sy;
			normal.y = tz*sx - ty*sz;
			normal.z = tx*sy - ty*sx;

			length = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
			normal.x /= length;
			normal.y /= length;
			normal.z /= length;
			normals.push_back(normal);

			/*Vertices[index + n].Color[0] = 1.0;
			Vertices[index + n].Color[1] = 0.0;
			Vertices[index + n].Color[2] = 0.0;
			Vertices[index + n].Color[3] = 1.0;

			float u = (float)i/sides;
			float v = ((float)j + u)/cs_sides;

			Vertices[index + n].TexCoord[0] = u;
			Vertices[index + n].TexCoord[1] = v;*/
		}
	}

	Utilities::Indexer::IndexVertexNormal(vertices, normals, geom.index, geom.position, geom.normal);
	return geom;
}

LowLevelGraphics::GeometryParameters Utilities::CreateSphereGeometry( float radius, unsigned int slices, unsigned int stacks )
{
	LowLevelGraphics::GeometryParameters geom;

	float varTheta = TWOPI / slices;
	float varPhi = PI / stacks;
	glm::vec3 vertex, vertexTop(0.0f, radius, 0.0f);
	float phi = varPhi;
	float yBottom = radius * cos(phi);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	// For the top of the sphere
	float radiusBottomCircle = sqrt(radius * radius - yBottom * yBottom);
	float theta = 0.0f;
	for(; theta < TWOPI - EPSILON; )
	{
		vertices.push_back(vertexTop);
		normals.push_back(glm::normalize(vertexTop));
		uvs.push_back(glm::vec2(0.5f,1.0f));
		vertex.x = radiusBottomCircle * cos(theta);
		vertex.y = yBottom;
		vertex.z = -radiusBottomCircle * sin(theta);
		vertices.push_back(vertex);
		normals.push_back(glm::normalize(vertex));
		uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));

		theta += varTheta;
		vertex.x = radiusBottomCircle * cos(theta);
		vertex.y = yBottom;
		vertex.z = -radiusBottomCircle * sin(theta);
		vertices.push_back(vertex);
		normals.push_back(glm::normalize(vertex));
		uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));
	}

	unsigned int nbMiddleStacks = stacks - 2;
	for (unsigned int i = 0; i < nbMiddleStacks; i++)
	{
		float yTop = yBottom;
		float radiusTopCircle = sqrt(radius * radius - yTop * yTop);
		phi += varPhi;
		yBottom = radius * cos(phi);
		radiusBottomCircle = sqrt(radius * radius - yBottom * yBottom);
		theta = 0.0f;

		for(; theta < TWOPI - EPSILON; )
		{
			glm::vec3 tempVertex01;
			tempVertex01.x = radiusTopCircle * cos(theta);
			tempVertex01.y = yTop;
			tempVertex01.z = -radiusTopCircle * sin(theta);
			vertices.push_back(tempVertex01);
			normals.push_back(glm::normalize(tempVertex01));
			uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-(phi-varPhi)/PI));

			vertex.x = radiusBottomCircle * cos(theta);
			vertex.y = yBottom;
			vertex.z = -radiusBottomCircle * sin(theta);
			vertices.push_back(vertex);
			normals.push_back(glm::normalize(vertex));
			uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));

			theta += varTheta;
			glm::vec3 tempVertex02;
			tempVertex02.x = radiusBottomCircle * cos(theta);
			tempVertex02.y = yBottom;
			tempVertex02.z = -radiusBottomCircle * sin(theta);
			vertices.push_back(tempVertex02);
			normals.push_back(glm::normalize(tempVertex02));
			uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));

			vertices.push_back(tempVertex01);
			normals.push_back(glm::normalize(tempVertex01));
			uvs.push_back(glm::vec2(1.0f-(theta-varTheta)/TWOPI, 1.0f-(phi-varPhi)/PI));

			vertices.push_back(tempVertex02);
			normals.push_back(glm::normalize(tempVertex02));
			uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));

			vertex.x = radiusTopCircle * cos(theta);
			vertex.y = yTop;
			vertex.z = -radiusTopCircle * sin(theta);
			vertices.push_back(vertex);
			normals.push_back(glm::normalize(vertex));
			uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-(phi-varPhi)/PI));
		}
	}

	// For the bottom of the sphere
	glm::vec3 bottomVertex(0.0f, -radius, 0.0f);
	theta = 0.0f;
	for(; theta < TWOPI - EPSILON; )
	{	
		vertex.x = radiusBottomCircle * cos(theta);
		vertex.y = yBottom;
		vertex.z = -radiusBottomCircle * sin(theta);
		vertices.push_back(vertex);
		normals.push_back(glm::normalize(vertex));
		uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));

		vertices.push_back(bottomVertex);
		normals.push_back(glm::normalize(bottomVertex));
		uvs.push_back(glm::vec2(0.5f, 0.0f));

		theta += varTheta;
		vertex.x = radiusBottomCircle * cos(theta);
		vertex.y = yBottom;
		vertex.z = -radiusBottomCircle * sin(theta);
		vertices.push_back(vertex);
		normals.push_back(glm::normalize(vertex));
		uvs.push_back(glm::vec2(1.0f-theta/TWOPI, 1.0f-phi/PI));
	}
	
	// Find the indices for the (vertices, uvs, normals)
	Utilities::Indexer::IndexVertexUvNormal(vertices, uvs, normals, geom.index, geom.position, geom.textureCoordinates, geom.normal);
	return geom;
}

LowLevelGraphics::GeometryParameters Utilities::CreateCubeGeometry( unsigned int length )
{
	ATUM_ASSERT( length != 0 );

	const float halfLength = (float)length/2;
	LowLevelGraphics::GeometryParameters cubeGeo;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texture;

	//create the eight vertices
	glm::vec3 verCoord[8];
	verCoord[0] = ( glm::vec3(halfLength,	-halfLength,	-halfLength) );//0
	verCoord[1] = ( glm::vec3(halfLength,	-halfLength,	halfLength) );//1
	verCoord[2] = ( glm::vec3(-halfLength,	-halfLength,	halfLength) );//2
	verCoord[3] = ( glm::vec3(-halfLength,	-halfLength,	-halfLength) );//3
	verCoord[4] = ( glm::vec3(halfLength,	halfLength,	-halfLength) );//4
	verCoord[5] = ( glm::vec3(halfLength,	halfLength,	halfLength) );//5
	verCoord[6] = ( glm::vec3(-halfLength,	halfLength,	halfLength) );//6
	verCoord[7] = ( glm::vec3(-halfLength,	halfLength,	-halfLength) );//7

	//generate vertices
	vertices.reserve(36);
	vertices.push_back(verCoord[0]);	vertices.push_back(verCoord[1]);	vertices.push_back(verCoord[2]);
	vertices.push_back(verCoord[4]);	vertices.push_back(verCoord[7]);	vertices.push_back(verCoord[5]);

	vertices.push_back(verCoord[0]);	vertices.push_back(verCoord[4]);	vertices.push_back(verCoord[1]);
	vertices.push_back(verCoord[1]);	vertices.push_back(verCoord[5]);	vertices.push_back(verCoord[2]);

	vertices.push_back(verCoord[2]);	vertices.push_back(verCoord[6]);	vertices.push_back(verCoord[7]);
	vertices.push_back(verCoord[4]);	vertices.push_back(verCoord[0]);	vertices.push_back(verCoord[3]);
	
	vertices.push_back(verCoord[3]);	vertices.push_back(verCoord[0]);	vertices.push_back(verCoord[2]);
	vertices.push_back(verCoord[7]);	vertices.push_back(verCoord[6]);	vertices.push_back(verCoord[5]);

	vertices.push_back(verCoord[4]);	vertices.push_back(verCoord[5]);	vertices.push_back(verCoord[1]);
	vertices.push_back(verCoord[5]);	vertices.push_back(verCoord[6]);	vertices.push_back(verCoord[2]);

	vertices.push_back(verCoord[3]);	vertices.push_back(verCoord[2]);	vertices.push_back(verCoord[7]);
	vertices.push_back(verCoord[7]);	vertices.push_back(verCoord[4]);	vertices.push_back(verCoord[3]);

	//create normals
	glm::vec3 norCoord[6];
	norCoord[0] = glm::vec3(0,-1,0);
	norCoord[1] = glm::vec3(0,1,0);
	norCoord[2] = glm::vec3(1,0,0);
	norCoord[3] = glm::vec3(0,0,1);
	norCoord[4] = glm::vec3(-1,0,0);
	norCoord[5] = glm::vec3(0,0,-1);

	normals.reserve(36);
	normals.push_back(norCoord[0]);	normals.push_back(norCoord[0]);	normals.push_back(norCoord[0]);
	normals.push_back(norCoord[1]);	normals.push_back(norCoord[1]);	normals.push_back(norCoord[1]);

	normals.push_back(norCoord[2]);	normals.push_back(norCoord[2]);	normals.push_back(norCoord[2]);
	normals.push_back(norCoord[3]);	normals.push_back(norCoord[3]);	normals.push_back(norCoord[3]);

	normals.push_back(norCoord[4]);	normals.push_back(norCoord[4]);	normals.push_back(norCoord[4]);
	normals.push_back(norCoord[5]);	normals.push_back(norCoord[5]);	normals.push_back(norCoord[5]);

	normals.push_back(norCoord[0]);	normals.push_back(norCoord[0]);	normals.push_back(norCoord[0]);
	normals.push_back(norCoord[1]);	normals.push_back(norCoord[1]);	normals.push_back(norCoord[1]);

	normals.push_back(norCoord[2]);	normals.push_back(norCoord[2]);	normals.push_back(norCoord[2]);
	normals.push_back(norCoord[3]);	normals.push_back(norCoord[3]);	normals.push_back(norCoord[3]);
	
	normals.push_back(norCoord[4]);	normals.push_back(norCoord[4]);	normals.push_back(norCoord[4]);
	normals.push_back(norCoord[5]);	normals.push_back(norCoord[5]);	normals.push_back(norCoord[5]);
	
	//create UV
	glm::vec2 uvCoord[4];
	uvCoord[2] = glm::vec2(0,0); //0
	uvCoord[1] = glm::vec2(1,0); //1
	uvCoord[0] = glm::vec2(1,1);  //2
	uvCoord[3] = glm::vec2(0,1);  //3

	texture.reserve(36);
	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);
	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[3]);

	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[3]);
	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[3]);

	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);
	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);

	texture.push_back(uvCoord[3]);	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[2]);
	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);	texture.push_back(uvCoord[3]);

	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);	texture.push_back(uvCoord[3]);
	texture.push_back(uvCoord[1]);	texture.push_back(uvCoord[2]);	texture.push_back(uvCoord[3]);

	texture.push_back(uvCoord[3]);	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[2]);
	texture.push_back(uvCoord[3]);	texture.push_back(uvCoord[0]);	texture.push_back(uvCoord[2]);

	Utilities::Indexer::IndexVertexUvNormal(vertices, texture, normals, cubeGeo.index, cubeGeo.position, cubeGeo.textureCoordinates, cubeGeo.normal);
	return cubeGeo;
}

LowLevelGraphics::GeometryParameters CreateSkyBoxGeometry(float sideBox)
{
	LowLevelGraphics::GeometryParameters skyBoxGeo;
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,-1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f, -1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f, -1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,-1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,-1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(-1.0f,1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,-1.0f,1.0f));
	skyBoxGeo.skyBoxCoords.push_back(glm::vec3(1.0f,1.0f,1.0f));

	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox, sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,-sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,-sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox, -sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,-sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,-sideBox,-sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(sideBox,-sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,sideBox,sideBox));
	skyBoxGeo.position.push_back(glm::vec3(-sideBox,-sideBox,sideBox));

	return skyBoxGeo;
}

}
}
