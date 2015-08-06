#ifndef _MARCHING_CUBES_H
#define _MARCHING_CUBES_H

#include "fileHandler.h"
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

class marchingCubes{

public:
    void setAllData(d3Buffer data, int themax, int themin, short int isolevel, int NX, int NY, int NZ);
    void perform(int offset);
    std::vector<TRIANGLE> getResult();
    bool GenerateStlFile(std::string path);
    void setIsolevel(short int isolevel);

private:
    int PolygoniseCube(GRIDCELL g, TRIANGLE *tri);
    XYZ VertexInterp(float isolevel, XYZ p1, XYZ p2, float valp1, float valp2);
	void CalcNormal(TRIANGLE &tri);

    int NX;
    int NY;
    int NZ;
    int themax;
    int themin;
    d3Buffer mData;
    short int isolevel; // , themax = 0, themin = 255;
    GRIDCELL grid;
    TRIANGLE triangles[10];
    std::vector<TRIANGLE> tri;
    int ntri = 0;
};

#endif // _MARCHING_CUBES_H
