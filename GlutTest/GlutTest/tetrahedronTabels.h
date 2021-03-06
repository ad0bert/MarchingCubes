#ifndef _TETRAHEDRON_TABELS_H
#define _TETRAHEDRON_TABELS_H

#include <glut.h>

// For any edge, if one vertex is inside of the surface and the other is outside of the surface
//  then the edge intersects the surface
// For each of the 4 vertices of the tetrahedron can be two possible states : either inside or outside of the surface
// For any tetrahedron the are 2^4=16 possible sets of vertex states
// This table lists the edges intersected by the surface for all 16 possible vertex states
// There are 6 edges.  For each entry in the table, if edge #n is intersected, then bit #n is set to 1

GLint TetrahedronEdgeFlags[16] =
{
	0x00, 0x0d, 0x13, 0x1e, 0x26, 0x2b, 0x35, 0x38, 0x38, 0x35, 0x2b, 0x26, 0x1e, 0x13, 0x0d, 0x00,
};


// For each of the possible vertex states listed in aiTetrahedronEdgeFlags there is a specific triangulation
// of the edge intersection points.  a2iTetrahedronTriangles lists all of them in the form of
// 0-2 edge triples with the list terminated by the invalid value -1.
//
// I generated this table by hand

GLint TetrahedronTriangles[16][7] =
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



#endif // _TETRAHEDRON_TABELS_H