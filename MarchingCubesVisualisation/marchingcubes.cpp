#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "marchingcubes.h"
#include "tabels.h"

void marchingCubes::setAllData(d3Buffer data, int themax, int themin, short int isolevel, int NX, int NY, int NZ){
    this->mData = data;
    this->themax = themax;
    this->themin = themin;
    this->isolevel = isolevel;
    this->NX = NX;
    this->NY = NY;
    this->NZ = NZ;
}
std::vector<TRIANGLE> marchingCubes::getResult(){
    return tri;
}

void marchingCubes::setIsolevel(short int isolevel){
    this->isolevel = isolevel;
}

void marchingCubes::generateSlice(int offset, int slice){
	int k = slice;
	for (int j = 0; j < NY - offset; j += offset) {
		for (int i = 0; i < NX - offset; i += offset) {
			grid.p[0].x = i;
			grid.p[0].y = j;
			grid.p[0].z = k;
			grid.val[0] = mData[i][j][k];
			grid.p[1].x = i + offset;
			grid.p[1].y = j;
			grid.p[1].z = k;
			grid.val[1] = mData[i + offset][j][k];
			grid.p[2].x = i + offset;
			grid.p[2].y = j + offset;
			grid.p[2].z = k;
			grid.val[2] = mData[i + offset][j + offset][k];
			grid.p[3].x = i;
			grid.p[3].y = j + offset;
			grid.p[3].z = k;
			grid.val[3] = mData[i][j + offset][k];
			grid.p[4].x = i;
			grid.p[4].y = j;
			grid.p[4].z = k + offset;
			grid.val[4] = mData[i][j][k + offset];
			grid.p[5].x = i + offset;
			grid.p[5].y = j;
			grid.p[5].z = k + offset;
			grid.val[5] = mData[i + offset][j][k + offset];
			grid.p[6].x = i + offset;
			grid.p[6].y = j + offset;
			grid.p[6].z = k + offset;
			grid.val[6] = mData[i + offset][j + offset][k + offset];
			grid.p[7].x = i;
			grid.p[7].y = j + offset;
			grid.p[7].z = k + offset;
			grid.val[7] = mData[i][j + offset][k + offset];
			int n = PolygoniseCube();
			for (int l = 0; l < n; l++){
				CalcNormal(triangles[l]);
				tri.push_back(triangles[l]);
			}
			ntri += n;
		}
	}
}

// Polygonise the grid
void marchingCubes::perform(int offset, int slice){
	tri.clear();
	ntri = 0;
    fprintf(stderr, "Polygonising data ...\n");

	if (slice != -1){
		for (int num = 0; num < offset && slice+num < NZ - 1; ++num)
			generateSlice(1, slice+num);
	}
	else{
		for (int i = 0; i < NZ - offset; i += offset) {
			if (i % (NZ / 10) == 0)
				fprintf(stderr, "   Slice %d of %d\n", i, NZ);
			generateSlice(offset, i);
		}
	}
}

bool marchingCubes::GenerateStlFile(std::string path){
    FILE *fptr = NULL;
    fprintf(stderr, "Writing triangles ...\n");
    if ((fptr = fopen(path.c_str(), "a+b")) == NULL) {
        fprintf(stderr, "Failed to open output file\n");
        return false;
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
    return true;
}

int marchingCubes::PolygoniseCube(){
    int currNtri = 0;
    int cubeindex = 0;
    XYZ vertlist[12];

    /*
    Determine the index into the edge table which
    tells us which vertices are inside of the surface
    */
    if (grid.val[0] < isolevel) cubeindex |= 1;
	if (grid.val[1] < isolevel) cubeindex |= 2;
	if (grid.val[2] < isolevel) cubeindex |= 4;
	if (grid.val[3] < isolevel) cubeindex |= 8;
	if (grid.val[4] < isolevel) cubeindex |= 16;
	if (grid.val[5] < isolevel) cubeindex |= 32;
	if (grid.val[6] < isolevel) cubeindex |= 64;
	if (grid.val[7] < isolevel) cubeindex |= 128;

    /* Cube is entirely in/out of the surface */
    if (edgeTable[cubeindex] == 0)
        return(0);

    /* Find the vertices where the surface intersects the cube */
    if (edgeTable[cubeindex] & 1) {
		vertlist[0] = VertexInterp(grid.p[0], grid.p[1], grid.val[0], grid.val[1]);
    }
    if (edgeTable[cubeindex] & 2) {
		vertlist[1] = VertexInterp(grid.p[1], grid.p[2], grid.val[1], grid.val[2]);
    }
    if (edgeTable[cubeindex] & 4) {
		vertlist[2] = VertexInterp(grid.p[2], grid.p[3], grid.val[2], grid.val[3]);
    }
    if (edgeTable[cubeindex] & 8) {
		vertlist[3] = VertexInterp(grid.p[3], grid.p[0], grid.val[3], grid.val[0]);
    }
    if (edgeTable[cubeindex] & 16) {
		vertlist[4] = VertexInterp(grid.p[4], grid.p[5], grid.val[4], grid.val[5]);
    }
    if (edgeTable[cubeindex] & 32) {
		vertlist[5] = VertexInterp(grid.p[5], grid.p[6], grid.val[5], grid.val[6]);
    }
    if (edgeTable[cubeindex] & 64) {
		vertlist[6] = VertexInterp(grid.p[6], grid.p[7], grid.val[6], grid.val[7]);
    }
    if (edgeTable[cubeindex] & 128) {
		vertlist[7] = VertexInterp(grid.p[7], grid.p[4], grid.val[7], grid.val[4]);
    }
    if (edgeTable[cubeindex] & 256) {
		vertlist[8] = VertexInterp(grid.p[0], grid.p[4], grid.val[0], grid.val[4]);
    }
    if (edgeTable[cubeindex] & 512) {
		vertlist[9] = VertexInterp(grid.p[1], grid.p[5], grid.val[1], grid.val[5]);
    }
    if (edgeTable[cubeindex] & 1024) {
		vertlist[10] = VertexInterp(grid.p[2], grid.p[6], grid.val[2], grid.val[6]);
    }
    if (edgeTable[cubeindex] & 2048) {
		vertlist[11] = VertexInterp(grid.p[3], grid.p[7], grid.val[3], grid.val[7]);
    }

    /* Create the triangles */
    for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
		triangles[currNtri].p[0] = vertlist[triTable[cubeindex][i]];
		triangles[currNtri].p[1] = vertlist[triTable[cubeindex][i + 1]];
		triangles[currNtri].p[2] = vertlist[triTable[cubeindex][i + 2]];
        currNtri++;
    }

    return(currNtri);
}

void marchingCubes::CalcNormal(TRIANGLE &tri){
	XYZ U;
	XYZ V;
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

XYZ marchingCubes::VertexInterp(XYZ p1, XYZ p2, float valp1, float valp2){
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
