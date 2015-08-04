#ifndef _MARCHING_CUBES
#define _MARCHING_CUBES

#include "glut.h"
#include "marchingBase.h"

class marchingCubes : public marchingBase{
public:	
	marchingCubes(helper *h){
		this->h = h;
	}
	//vMarchCube1 performs the Marching Cubes algorithm on a single cube
	GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);

};


#endif // _MARCHING_CUBES