#ifndef _MARCHING_CUBES_H
#define _MARCHING_CUBES_H

#include "fileHandler.h"

typedef struct {
    float x, y, z;
} XYZ;

typedef struct {
    XYZ p[8];		// corners
    float val[8];	// isolevel of one corner
} GRIDCELL;

typedef struct {
    XYZ p[3];		// Vertices
    XYZ n;			// Normal
} TRIANGLE;

#define ABS(x) (x < 0 ? -(x) : (x))

class marchingCubes{

public:
    void setAllData(d3Buffer data, short int isolevel);
    void perform(int offset, int slice = -1);
    std::vector<TRIANGLE> getResult();
    bool generateStlFile(std::string path);
    void setIsolevel(short int isolevel);
    void setSlicing(bool enable);
private:
	// performing the mc for one slice of the input
	void generateSlice(int offset, int slice);
	// performs the mc-algo for one cube
	void polygoniseCube(GRIDCELL grid, std::vector<TRIANGLE> &triangles);
    
	// math. helper functions
	XYZ vertexInterp(XYZ p1, XYZ p2, float valp1, float valp2);
	void calcNormal(TRIANGLE &tri);

    d3Buffer mData;					// RAW input data
    short int mIsolevel;			// Treshhold value
    
	std::vector<TRIANGLE> mResult;	// list of resulting triangles after the mc-algo
};

#endif // _MARCHING_CUBES_H
