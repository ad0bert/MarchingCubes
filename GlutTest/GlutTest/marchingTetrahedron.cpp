#include "marchingTetrahedron.h"
#include "helper.h"

//a2iTetrahedronEdgeConnection lists the index of the endpoint vertices for each of the 6 edges of the tetrahedron
static const GLint a2iTetrahedronEdgeConnection[6][2] =
{
	{ 0, 1 }, { 1, 2 }, { 2, 0 }, { 0, 3 }, { 1, 3 }, { 2, 3 }
};

//a2iTetrahedronEdgeConnection lists the index of verticies from a cube 
// that made up each of the six tetrahedrons within the cube
static const GLint a2iTetrahedronsInACube[6][4] =
{
	{ 0, 5, 1, 6 },
	{ 0, 1, 2, 6 },
	{ 0, 2, 3, 6 },
	{ 0, 3, 7, 6 },
	{ 0, 7, 4, 6 },
	{ 0, 4, 5, 6 },
};

// For any edge, if one vertex is inside of the surface and the other is outside of the surface
//  then the edge intersects the surface
// For each of the 4 vertices of the tetrahedron can be two possible states : either inside or outside of the surface
// For any tetrahedron the are 2^4=16 possible sets of vertex states
// This table lists the edges intersected by the surface for all 16 possible vertex states
// There are 6 edges.  For each entry in the table, if edge #n is intersected, then bit #n is set to 1

GLint aiTetrahedronEdgeFlags[16] =
{
	0x00, 0x0d, 0x13, 0x1e, 0x26, 0x2b, 0x35, 0x38, 0x38, 0x35, 0x2b, 0x26, 0x1e, 0x13, 0x0d, 0x00,
};


// For each of the possible vertex states listed in aiTetrahedronEdgeFlags there is a specific triangulation
// of the edge intersection points.  a2iTetrahedronTriangles lists all of them in the form of
// 0-2 edge triples with the list terminated by the invalid value -1.
//
// I generated this table by hand

GLint a2iTetrahedronTriangles[16][7] =
{
	{ -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 3, 2, -1, -1, -1, -1 },
	{ 0, 1, 4, -1, -1, -1, -1 },
	{ 1, 4, 2, 2, 4, 3, -1 },

	{ 1, 2, 5, -1, -1, -1, -1 },
	{ 0, 3, 5, 0, 5, 1, -1 },
	{ 0, 2, 5, 0, 5, 4, -1 },
	{ 5, 4, 3, -1, -1, -1, -1 },

	{ 3, 4, 5, -1, -1, -1, -1 },
	{ 4, 5, 0, 5, 2, 0, -1 },
	{ 1, 5, 0, 5, 3, 0, -1 },
	{ 5, 2, 1, -1, -1, -1, -1 },

	{ 3, 4, 2, 2, 4, 1, -1 },
	{ 4, 1, 0, -1, -1, -1, -1 },
	{ 2, 3, 0, -1, -1, -1, -1 },
	{ -1, -1, -1, -1, -1, -1, -1 },
};

GLvoid marchingTetrahedron::MarchTetrahedron(GLvector *pasTetrahedronPosition, GLfloat *pafTetrahedronValue)
{
	extern GLint aiTetrahedronEdgeFlags[16];
	extern GLint a2iTetrahedronTriangles[16][7];

	GLint iEdge, iVert0, iVert1, iEdgeFlags, iTriangle, iCorner, iVertex, iFlagIndex = 0;
	GLfloat fOffset, fInvOffset, fValue = 0.0;
	GLvector asEdgeVertex[6];
	GLvector asEdgeNorm[6];
	GLvector sColor;

	//Find which vertices are inside of the surface and which are outside
	for (iVertex = 0; iVertex < 4; iVertex++)
	{
		if (pafTetrahedronValue[iVertex] <= h->fTargetValue)
			iFlagIndex |= 1 << iVertex;
	}

	//Find which edges are intersected by the surface
	iEdgeFlags = aiTetrahedronEdgeFlags[iFlagIndex];

	//If the tetrahedron is entirely inside or outside of the surface, then there will be no intersections
	if (iEdgeFlags == 0)
	{
		return;
	}
	//Find the point of intersection of the surface with each edge
	// Then find the normal to the surface at those points
	for (iEdge = 0; iEdge < 6; iEdge++)
	{
		//if there is an intersection on this edge
		if (iEdgeFlags & (1 << iEdge))
		{
			iVert0 = a2iTetrahedronEdgeConnection[iEdge][0];
			iVert1 = a2iTetrahedronEdgeConnection[iEdge][1];
			fOffset = fGetOffset(pafTetrahedronValue[iVert0], pafTetrahedronValue[iVert1], h->fTargetValue);
			fInvOffset = 1.0 - fOffset;

			asEdgeVertex[iEdge].fX = fInvOffset*pasTetrahedronPosition[iVert0].fX + fOffset*pasTetrahedronPosition[iVert1].fX;
			asEdgeVertex[iEdge].fY = fInvOffset*pasTetrahedronPosition[iVert0].fY + fOffset*pasTetrahedronPosition[iVert1].fY;
			asEdgeVertex[iEdge].fZ = fInvOffset*pasTetrahedronPosition[iVert0].fZ + fOffset*pasTetrahedronPosition[iVert1].fZ;

			vGetNormal(asEdgeNorm[iEdge], asEdgeVertex[iEdge].fX, asEdgeVertex[iEdge].fY, asEdgeVertex[iEdge].fZ);
		}
	}
	//Draw the triangles that were found.  There can be up to 2 per tetrahedron
	for (iTriangle = 0; iTriangle < 2; iTriangle++)
	{
		if (a2iTetrahedronTriangles[iFlagIndex][3 * iTriangle] < 0)
			break;

		for (iCorner = 0; iCorner < 3; iCorner++)
		{
			iVertex = a2iTetrahedronTriangles[iFlagIndex][3 * iTriangle + iCorner];

			vGetColor(sColor, asEdgeVertex[iVertex], asEdgeNorm[iVertex]);
			glColor3f(sColor.fX, sColor.fY, sColor.fZ);
			glNormal3f(asEdgeNorm[iVertex].fX, asEdgeNorm[iVertex].fY, asEdgeNorm[iVertex].fZ);
			glVertex3f(asEdgeVertex[iVertex].fX, asEdgeVertex[iVertex].fY, asEdgeVertex[iVertex].fZ);
		}
	}
}

GLvoid marchingTetrahedron::MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale){
	GLint iVertex, iTetrahedron, iVertexInACube;
	GLvector asCubePosition[8];
	GLfloat  afCubeValue[8];
	GLvector asTetrahedronPosition[4];
	GLfloat  afTetrahedronValue[4];

	//Make a local copy of the cube's corner positions
	for (iVertex = 0; iVertex < 8; iVertex++)
	{
		asCubePosition[iVertex].fX = fX + a2fVertexOffset[iVertex][0] * fScale;
		asCubePosition[iVertex].fY = fY + a2fVertexOffset[iVertex][1] * fScale;
		asCubePosition[iVertex].fZ = fZ + a2fVertexOffset[iVertex][2] * fScale;
	}

	//Make a local copy of the cube's corner values
	for (iVertex = 0; iVertex < 8; iVertex++)
	{
		afCubeValue[iVertex] = h->fSample(asCubePosition[iVertex].fX,
			asCubePosition[iVertex].fY,
			asCubePosition[iVertex].fZ);
	}

	for (iTetrahedron = 0; iTetrahedron < 6; iTetrahedron++)
	{
		for (iVertex = 0; iVertex < 4; iVertex++)
		{
			iVertexInACube = a2iTetrahedronsInACube[iTetrahedron][iVertex];
			asTetrahedronPosition[iVertex].fX = asCubePosition[iVertexInACube].fX;
			asTetrahedronPosition[iVertex].fY = asCubePosition[iVertexInACube].fY;
			asTetrahedronPosition[iVertex].fZ = asCubePosition[iVertexInACube].fZ;
			afTetrahedronValue[iVertex] = afCubeValue[iVertexInACube];
		}
		MarchTetrahedron(asTetrahedronPosition, afTetrahedronValue);
	}
}