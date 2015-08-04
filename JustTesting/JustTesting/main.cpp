#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <conio.h>
#include "dbh.h"
#include "fileHandler.h"
#include "tabels.h"
using namespace std;
/*
Simple test of the Marching Cubes code found in paulslib found here
Very poorly written with lots of assumptions, designed to give the
basic idea of how to call PolygoniseCube().
ps: code formateed for tab stops of 3 characters.
pps: One would normally want to calculate normals as well.
*/

typedef struct {
	float x, y, z;
} XYZ;

typedef struct {
	XYZ p[8];
	XYZ n[8];
	float val[8];
} GRIDCELL;

typedef struct {
	XYZ p[3];         /* Vertices */
	XYZ c;            /* Centroid */
	XYZ n[3];         /* Normal   */
} TRIANGLE;

#define ABS(x) (x < 0 ? -(x) : (x))

// Prototypes
int PolygoniseCube(GRIDCELL, float, TRIANGLE *);
XYZ VertexInterp(float, XYZ, XYZ, float, float);

// "C:\Users\Adobert\Downloads\Ortner\Cubic_CT_Head.hdr" "C:\Users\Adobert\Downloads\Ortner\Cubic_CT_Head.img"
int main(int argc, char **argv)
{
	fileHandler *header = new fileHandler(argv[1], hdr);
	fileHandler *image = new fileHandler(argv[2], img);
	header->readFile();
	image->setHdr(header->getHdr());
	image->readFile();

	int NX = header->getHdr().dime.dim[1];
	int NY = header->getHdr().dime.dim[1];
	int NZ = header->getHdr().dime.dim[1];

	int themax = header->getHdr().dime.glmax;
	int themin = header->getHdr().dime.glmin;

	d3Buffer data = image->getData();
	short int isolevel = 200; // , themax = 0, themin = 255;
	GRIDCELL grid;
	TRIANGLE triangles[10];
	std::vector<TRIANGLE> tri;
	//TRIANGLE *tri = NULL;
	int ntri = 0;

	fprintf(stderr, "Volumetric data range: %d -> %d\n", themin, themax);

	// Polygonise the grid 
	fprintf(stderr, "Polygonising data ...\n");
	for (int i = 0; i < NX - 1; i++) {
		if (i % (NX / 10) == 0)
			fprintf(stderr, "   Slice %d of %d\n", i, NX);
		for (int j = 0; j < NY - 1; j++) {
			for (int k = 0; k < NZ - 1; k++) {
				grid.p[0].x = i;
				grid.p[0].y = j;
				grid.p[0].z = k;
				grid.val[0] = data[i][j][k];
				grid.p[1].x = i + 1;
				grid.p[1].y = j;
				grid.p[1].z = k;
				grid.val[1] = data[i + 1][j][k];
				grid.p[2].x = i + 1;
				grid.p[2].y = j + 1;
				grid.p[2].z = k;
				grid.val[2] = data[i + 1][j + 1][k];
				grid.p[3].x = i;
				grid.p[3].y = j + 1;
				grid.p[3].z = k;
				grid.val[3] = data[i][j + 1][k];
				grid.p[4].x = i;
				grid.p[4].y = j;
				grid.p[4].z = k + 1;
				grid.val[4] = data[i][j][k + 1];
				grid.p[5].x = i + 1;
				grid.p[5].y = j;
				grid.p[5].z = k + 1;
				grid.val[5] = data[i + 1][j][k + 1];
				grid.p[6].x = i + 1;
				grid.p[6].y = j + 1;
				grid.p[6].z = k + 1;
				grid.val[6] = data[i + 1][j + 1][k + 1];
				grid.p[7].x = i;
				grid.p[7].y = j + 1;
				grid.p[7].z = k + 1;
				grid.val[7] = data[i][j + 1][k + 1];
				int n = PolygoniseCube(grid, isolevel, triangles);
				for (int l = 0; l < n; l++)
					tri.push_back(triangles[l]);
				ntri += n;
			}
		}
	}
	fprintf(stderr, "Total of %d triangles\n", ntri);

	// create stl file
	FILE *fptr = NULL;
	fprintf(stderr, "Writing triangles ...\n");
	if ((fptr = fopen("output.stl", "a+b")) == NULL) {
		fprintf(stderr, "Failed to open output file\n");
		return -1;
	}
	char fileHeader[81] = "solid Test Head";
	char bytes[3] = { 0x00, 0x00 };
	fwrite(&fileHeader, sizeof(fileHeader)-1, 1, fptr);
	fwrite(&ntri, sizeof(int), 1, fptr);
	for (int i = 0; i < ntri; i++) {
		fwrite(&tri[i].n, sizeof(float), 3, fptr);
		for (int k = 0; k < 3; k++)  {
			fwrite(&tri[i].p[k], sizeof(float), 3, fptr);
		}
		fwrite(bytes, 2, 1, fptr);
	}
	fclose(fptr);
	delete (header);
	delete (image);
	return 0;
}

/*-------------------------------------------------------------------------
Given a grid cell and an isolevel, calculate the triangular
facets requied to represent the isosurface through the cell.
Return the number of triangular facets, the array "triangles"
will be loaded up with the vertices at most 5 triangular facets.
0 will be returned if the grid cell is either totally above
of totally below the isolevel.
*/
int PolygoniseCube(GRIDCELL g, float iso, TRIANGLE *tri)
{
	int i, ntri = 0;
	int cubeindex;
	XYZ vertlist[12];

	/*
	Determine the index into the edge table which
	tells us which vertices are inside of the surface
	*/
	cubeindex = 0;
	if (g.val[0] < iso) cubeindex |= 1;
	if (g.val[1] < iso) cubeindex |= 2;
	if (g.val[2] < iso) cubeindex |= 4;
	if (g.val[3] < iso) cubeindex |= 8;
	if (g.val[4] < iso) cubeindex |= 16;
	if (g.val[5] < iso) cubeindex |= 32;
	if (g.val[6] < iso) cubeindex |= 64;
	if (g.val[7] < iso) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return(0);

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1) {
		vertlist[0] = VertexInterp(iso, g.p[0], g.p[1], g.val[0], g.val[1]);
	}
	if (edgeTable[cubeindex] & 2) {
		vertlist[1] = VertexInterp(iso, g.p[1], g.p[2], g.val[1], g.val[2]);
	}
	if (edgeTable[cubeindex] & 4) {
		vertlist[2] = VertexInterp(iso, g.p[2], g.p[3], g.val[2], g.val[3]);
	}
	if (edgeTable[cubeindex] & 8) {
		vertlist[3] = VertexInterp(iso, g.p[3], g.p[0], g.val[3], g.val[0]);
	}
	if (edgeTable[cubeindex] & 16) {
		vertlist[4] = VertexInterp(iso, g.p[4], g.p[5], g.val[4], g.val[5]);
	}
	if (edgeTable[cubeindex] & 32) {
		vertlist[5] = VertexInterp(iso, g.p[5], g.p[6], g.val[5], g.val[6]);
	}
	if (edgeTable[cubeindex] & 64) {
		vertlist[6] = VertexInterp(iso, g.p[6], g.p[7], g.val[6], g.val[7]);
	}
	if (edgeTable[cubeindex] & 128) {
		vertlist[7] = VertexInterp(iso, g.p[7], g.p[4], g.val[7], g.val[4]);
	}
	if (edgeTable[cubeindex] & 256) {
		vertlist[8] = VertexInterp(iso, g.p[0], g.p[4], g.val[0], g.val[4]);
	}
	if (edgeTable[cubeindex] & 512) {
		vertlist[9] = VertexInterp(iso, g.p[1], g.p[5], g.val[1], g.val[5]);
	}
	if (edgeTable[cubeindex] & 1024) {
		vertlist[10] = VertexInterp(iso, g.p[2], g.p[6], g.val[2], g.val[6]);
	}
	if (edgeTable[cubeindex] & 2048) {
		vertlist[11] = VertexInterp(iso, g.p[3], g.p[7], g.val[3], g.val[7]);
	}

	/* Create the triangles */
	for (i = 0; triTable[cubeindex][i] != -1; i += 3) {
		tri[ntri].p[0] = vertlist[triTable[cubeindex][i]];
		tri[ntri].p[1] = vertlist[triTable[cubeindex][i + 1]];
		tri[ntri].p[2] = vertlist[triTable[cubeindex][i + 2]];
		ntri++;
	}

	return(ntri);
}

/*-------------------------------------------------------------------------
Return the point between two points in the same ratio as
isolevel is between valp1 and valp2
*/
XYZ VertexInterp(float isolevel, XYZ p1, XYZ p2, float valp1, float valp2)
{
	float mu;
	XYZ p;

	if (ABS(isolevel - valp1) < 0.00001)
		return(p1);
	if (ABS(isolevel - valp2) < 0.00001)
		return(p2);
	if (ABS(valp1 - valp2) < 0.00001)
		return(p1);
	mu = (isolevel - valp1) / (valp2 - valp1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return(p);
}


