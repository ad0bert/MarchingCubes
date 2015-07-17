#ifndef _MARCHING_CUBES
#define _MARCHING_CUBES

#include "glut.h"
#include "marchingBase.h"


class marchingCubes : marchingBase{
public:	
	GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale) override;

};


#endif // _MARCHING_CUBES