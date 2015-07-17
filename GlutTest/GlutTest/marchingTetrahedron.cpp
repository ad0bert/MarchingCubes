#include "marchingTetrahedron.h"

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
		afCubeValue[iVertex] = fSample(asCubePosition[iVertex].fX,
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
		vMarchTetrahedron(asTetrahedronPosition, afTetrahedronValue);
	}
}