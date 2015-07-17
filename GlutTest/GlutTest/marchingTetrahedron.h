#ifndef _MARCHING_TETRAHEDRON
#define _MARCHING_TETRAHEDRON

#include "marchingBase.h"
#include <glut.h>

class marchingTetrahedron : public marchingBase{
	GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale) override;
};


#endif // _MARCHING_TETRAHEDRON