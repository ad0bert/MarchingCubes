#ifndef _MARCHING_BASE
#define _MARCHING_BASE

#include <glut.h>
#include "helper.h"

class marchingBase{
public:
	virtual GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale) = 0;
	//vMarchingCubes iterates over the entire dataset, calling vMarchCube on each cube
	GLvoid MarchingCubes();

protected:
	//fGetOffset finds the approximate point of intersection of the surface
	// between two points with the values fValue1 and fValue2
	GLfloat fGetOffset(GLfloat fValue1, GLfloat fValue2, GLfloat fValueDesired);
	//vGetColor generates a color from a given position and normal of a point
	GLvoid vGetColor(GLvector &rfColor, GLvector &rfPosition, GLvector &rfNormal);
	//vGetNormal() finds the gradient of the scalar field at a point
	//This gradient can be used as a very accurate vertx normal for lighting calculations
	GLvoid vGetNormal(GLvector &rfNormal, GLfloat fX, GLfloat fY, GLfloat fZ);
	GLvoid vNormalizeVector(GLvector &rfVectorResult, GLvector &rfVectorSource);

	helper *h;
};


#endif // _MARCHING_BASE