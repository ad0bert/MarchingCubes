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

void marchingCubes::perform(int offset){
    // Polygonise the grid
	tri.clear();
	ntri = 0;
    fprintf(stderr, "Polygonising data ...\n");
	for (int i = 0; i < NX - offset; i += offset) {
        if (i % (NX / 10) == 0)
            fprintf(stderr, "   Slice %d of %d\n", i, NX);
        for (int j = 0; j < NY - offset; j += offset) {
			for (int k = 0; k < NZ - offset; k += offset) {
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
                int n = PolygoniseCube(grid, triangles);
				for (int l = 0; l < n; l++){
					CalcNormal(triangles[l]);
					tri.push_back(triangles[l]);
				}
                ntri += n;
            }
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
        fwrite(&tri[i].n[0], sizeof(float), 3, fptr);
        for (int k = 0; k < 3; k++)  {
            fwrite(&tri[i].p[k], sizeof(float), 3, fptr);
        }
        fwrite(bytes, 2, 1, fptr);
    }
    fclose(fptr);
    return true;
}

int marchingCubes::PolygoniseCube(GRIDCELL g, TRIANGLE *tri){
    int currNtri = 0;
    int cubeindex = 0;
    XYZ vertlist[12];

    /*
    Determine the index into the edge table which
    tells us which vertices are inside of the surface
    */
    if (g.val[0] < isolevel) cubeindex |= 1;
	if (g.val[1] < isolevel) cubeindex |= 2;
	if (g.val[2] < isolevel) cubeindex |= 4;
	if (g.val[3] < isolevel) cubeindex |= 8;
	if (g.val[4] < isolevel) cubeindex |= 16;
	if (g.val[5] < isolevel) cubeindex |= 32;
	if (g.val[6] < isolevel) cubeindex |= 64;
	if (g.val[7] < isolevel) cubeindex |= 128;

    /* Cube is entirely in/out of the surface */
    if (edgeTable[cubeindex] == 0)
        return(0);

    /* Find the vertices where the surface intersects the cube */
    if (edgeTable[cubeindex] & 1) {
		vertlist[0] = VertexInterp(isolevel, g.p[0], g.p[1], g.val[0], g.val[1]);
    }
    if (edgeTable[cubeindex] & 2) {
		vertlist[1] = VertexInterp(isolevel, g.p[1], g.p[2], g.val[1], g.val[2]);
    }
    if (edgeTable[cubeindex] & 4) {
		vertlist[2] = VertexInterp(isolevel, g.p[2], g.p[3], g.val[2], g.val[3]);
    }
    if (edgeTable[cubeindex] & 8) {
		vertlist[3] = VertexInterp(isolevel, g.p[3], g.p[0], g.val[3], g.val[0]);
    }
    if (edgeTable[cubeindex] & 16) {
		vertlist[4] = VertexInterp(isolevel, g.p[4], g.p[5], g.val[4], g.val[5]);
    }
    if (edgeTable[cubeindex] & 32) {
		vertlist[5] = VertexInterp(isolevel, g.p[5], g.p[6], g.val[5], g.val[6]);
    }
    if (edgeTable[cubeindex] & 64) {
		vertlist[6] = VertexInterp(isolevel, g.p[6], g.p[7], g.val[6], g.val[7]);
    }
    if (edgeTable[cubeindex] & 128) {
		vertlist[7] = VertexInterp(isolevel, g.p[7], g.p[4], g.val[7], g.val[4]);
    }
    if (edgeTable[cubeindex] & 256) {
		vertlist[8] = VertexInterp(isolevel, g.p[0], g.p[4], g.val[0], g.val[4]);
    }
    if (edgeTable[cubeindex] & 512) {
		vertlist[9] = VertexInterp(isolevel, g.p[1], g.p[5], g.val[1], g.val[5]);
    }
    if (edgeTable[cubeindex] & 1024) {
		vertlist[10] = VertexInterp(isolevel, g.p[2], g.p[6], g.val[2], g.val[6]);
    }
    if (edgeTable[cubeindex] & 2048) {
		vertlist[11] = VertexInterp(isolevel, g.p[3], g.p[7], g.val[3], g.val[7]);
    }

    /* Create the triangles */
    for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
        tri[currNtri].p[0] = vertlist[triTable[cubeindex][i]];
        tri[currNtri].p[1] = vertlist[triTable[cubeindex][i + 1]];
        tri[currNtri].p[2] = vertlist[triTable[cubeindex][i + 2]];
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

	tri.n[0].x = (U.y * V.z) - (U.z * V.y);
	tri.n[0].y = (U.z * V.x) - (U.x * V.z);
	tri.n[0].z = (U.x * V.y) - (U.y * V.x);

}

XYZ marchingCubes::VertexInterp(float isolevel, XYZ p1, XYZ p2, float valp1, float valp2){
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
