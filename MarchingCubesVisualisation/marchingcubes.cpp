#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include "marchingcubes.h"
#include "tabels.h"

void marchingCubes::setAllData(d3Buffer data, short int isolevel){
	this->mData = data;
	this->mIsolevel = isolevel;
}

std::vector<TRIANGLE> marchingCubes::getResult(){
	return mResult;
}

void marchingCubes::setIsolevel(short int isolevel){
	this->mIsolevel = isolevel;
}

void marchingCubes::generateSlice(int offset, int slice){
	int k = slice;
	static GRIDCELL grid;
	static std::vector<TRIANGLE> triangles;
	for (int j = 0; j < mData[0].size() - offset; j += offset) {
		for (int i = 0; i < mData.size() - offset; i += offset) {
			grid.p[0].x = (float)i;
			grid.p[0].y = (float)j;
			grid.p[0].z = (float)k;
			grid.val[0] = (float)mData[i][j][k];
			grid.p[1].x = (float)i + offset;
			grid.p[1].y = (float)j;
			grid.p[1].z = (float)k;
			grid.val[1] = (float)mData[i + offset][j][k];
			grid.p[2].x = (float)i + offset;
			grid.p[2].y = (float)j + offset;
			grid.p[2].z = (float)k;
			grid.val[2] = (float)mData[i + offset][j + offset][k];
			grid.p[3].x = (float)i;
			grid.p[3].y = (float)j + offset;
			grid.p[3].z = (float)k;
			grid.val[3] = (float)mData[i][j + offset][k];
			grid.p[4].x = (float)i;
			grid.p[4].y = (float)j;
			grid.p[4].z = (float)k + offset;
			grid.val[4] = (float)mData[i][j][k + offset];
			grid.p[5].x = (float)i + offset;
			grid.p[5].y = (float)j;
			grid.p[5].z = (float)k + offset;
			grid.val[5] = (float)mData[i + offset][j][k + offset];
			grid.p[6].x = (float)i + offset;
			grid.p[6].y = (float)j + offset;
			grid.p[6].z = (float)k + offset;
			grid.val[6] = (float)mData[i + offset][j + offset][k + offset];
			grid.p[7].x = (float)i;
			grid.p[7].y = (float)j + offset;
			grid.p[7].z = (float)k + offset;
			grid.val[7] = (float)mData[i][j + offset][k + offset];
			polygoniseCube(grid, triangles);
			for (int l = 0; l < triangles.size(); l++){
				calcNormal(triangles[l]);
				mResult.push_back(triangles[l]);
			}
		}
	}
}

// Polygonise the grid
void marchingCubes::perform(int offset, int slice){
	mResult.clear();
	fprintf(stderr, "Polygonising data ...\n");

	if (slice != -1){
		for (int num = 0; num < offset && slice + num < mData[0][0].size() - 1; ++num)
			generateSlice(1, slice + num);
	}
	else{
		for (int i = 0; i < mData[0][0].size() - offset; i += offset) {
			if (i % (mData[0][0].size() / 10) == 0)
				fprintf(stderr, "   Slice %d of %d\n", i, mData[0][0].size());
			generateSlice(offset, i);
		}
	}
}

bool marchingCubes::generateStlFile(std::string path){
	FILE *fptr = NULL;
	
	int sizeResult = mResult.size();
	fprintf(stderr, "Writing triangles ...\n");
	if ((fptr = fopen(path.c_str(), "a+b")) == NULL) {
		fprintf(stderr, "Failed to open output file\n");
		return false;
	}
	char fileHeader[81] = "solid Test Head";
	char bytes[3] = { 0x00, 0x00 };
	fwrite(&fileHeader, sizeof(fileHeader)-1, 1, fptr);
	fwrite(&sizeResult, sizeof(int), 1, fptr);
	for (int i = 0; i < mResult.size(); i++) {
		fwrite(&mResult[i].n, sizeof(float), 3, fptr);
		for (int k = 0; k < 3; k++)  {
			fwrite(&mResult[i].p[k], sizeof(float), 3, fptr);
		}
		fwrite(bytes, 2, 1, fptr);
	}
	fclose(fptr);
	return true;
}

void marchingCubes::polygoniseCube(GRIDCELL grid, std::vector<TRIANGLE> &triangles){
	triangles.clear();
	int cubeindex = 0;
	static XYZ zero = { 0, 0, 0 };
	static std::vector<XYZ> vertlist = { zero, zero, zero, zero, 
										 zero, zero, zero, zero, 
										 zero, zero, zero, zero};
	/*
	Determine the index into the edge table which
	tells us which vertices are inside of the surface
	*/
	if (grid.val[0] < mIsolevel) cubeindex |= 1;
	if (grid.val[1] < mIsolevel) cubeindex |= 2;
	if (grid.val[2] < mIsolevel) cubeindex |= 4;
	if (grid.val[3] < mIsolevel) cubeindex |= 8;
	if (grid.val[4] < mIsolevel) cubeindex |= 16;
	if (grid.val[5] < mIsolevel) cubeindex |= 32;
	if (grid.val[6] < mIsolevel) cubeindex |= 64;
	if (grid.val[7] < mIsolevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return;

	/* Find the vertices where the surface intersects the cube */
	if (edgeTable[cubeindex] & 1) {
		vertlist[0] = vertexInterp(grid.p[0], grid.p[1], grid.val[0], grid.val[1]);
	}
	if (edgeTable[cubeindex] & 2) {
		vertlist[1] = vertexInterp(grid.p[1], grid.p[2], grid.val[1], grid.val[2]);
	}
	if (edgeTable[cubeindex] & 4) {
		vertlist[2] = vertexInterp(grid.p[2], grid.p[3], grid.val[2], grid.val[3]);
	}
	if (edgeTable[cubeindex] & 8) {
		vertlist[3] = vertexInterp(grid.p[3], grid.p[0], grid.val[3], grid.val[0]);
	}
	if (edgeTable[cubeindex] & 16) {
		vertlist[4] = vertexInterp(grid.p[4], grid.p[5], grid.val[4], grid.val[5]);
	}
	if (edgeTable[cubeindex] & 32) {
		vertlist[5] = vertexInterp(grid.p[5], grid.p[6], grid.val[5], grid.val[6]);
	}
	if (edgeTable[cubeindex] & 64) {
		vertlist[6] = vertexInterp(grid.p[6], grid.p[7], grid.val[6], grid.val[7]);
	}
	if (edgeTable[cubeindex] & 128) {
		vertlist[7] = vertexInterp(grid.p[7], grid.p[4], grid.val[7], grid.val[4]);
	}
	if (edgeTable[cubeindex] & 256) {
		vertlist[8] = vertexInterp(grid.p[0], grid.p[4], grid.val[0], grid.val[4]);
	}
	if (edgeTable[cubeindex] & 512) {
		vertlist[9] = vertexInterp(grid.p[1], grid.p[5], grid.val[1], grid.val[5]);
	}
	if (edgeTable[cubeindex] & 1024) {
		vertlist[10] = vertexInterp(grid.p[2], grid.p[6], grid.val[2], grid.val[6]);
	}
	if (edgeTable[cubeindex] & 2048) {
		vertlist[11] = vertexInterp(grid.p[3], grid.p[7], grid.val[3], grid.val[7]);
	}

	/* Create the triangles */
	static TRIANGLE tri;
	for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
		tri.p[0] = vertlist[triTable[cubeindex][i]];
		tri.p[1] = vertlist[triTable[cubeindex][i + 1]];
		tri.p[2] = vertlist[triTable[cubeindex][i + 2]];
		triangles.push_back(tri);
	}
}

void marchingCubes::calcNormal(TRIANGLE &tri){
	static XYZ U;
	static XYZ V;
	U.x = tri.p[1].x - tri.p[0].x;
	U.y = tri.p[1].y - tri.p[0].y;
	U.z = tri.p[1].z - tri.p[0].z;

	V.x = tri.p[2].x - tri.p[0].x;
	V.y = tri.p[2].y - tri.p[0].y;
	V.z = tri.p[2].z - tri.p[0].z;

	tri.n.x = (U.y * V.z) - (U.z * V.y);
	tri.n.y = (U.z * V.x) - (U.x * V.z);
	tri.n.z = (U.x * V.y) - (U.y * V.x);

}

XYZ marchingCubes::vertexInterp(XYZ p1, XYZ p2, float valp1, float valp2){
	float mu;
	static XYZ p;

	if (ABS(mIsolevel - valp1) < 0.00001)
		return(p1);
	if (ABS(mIsolevel - valp2) < 0.00001)
		return(p2);
	if (ABS(valp1 - valp2) < 0.00001)
		return(p1);
	mu = (mIsolevel - valp1) / (valp2 - valp1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return(p);
}
