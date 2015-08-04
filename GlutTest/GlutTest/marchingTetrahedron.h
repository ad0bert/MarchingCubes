#ifndef _MARCHING_TETRAHEDRON
#define _MARCHING_TETRAHEDRON

#include "marchingBase.h"

class marchingTetrahedron : public marchingBase{
public:
	marchingTetrahedron(helper *h){
		this->h = h;
	}
	//vMarchCube2 performs the Marching Tetrahedrons algorithm on a single cube by making six calls to vMarchTetrahedron
	GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);

private:
	//vMarchTetrahedron performs the Marching Tetrahedrons algorithm on a single tetrahedron
	GLvoid MarchTetrahedron(GLvector *pasTetrahedronPosition, GLfloat *pafTetrahedronValue);
};


#endif // _MARCHING_TETRAHEDRON