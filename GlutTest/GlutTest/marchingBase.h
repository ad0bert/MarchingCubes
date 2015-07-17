#ifndef _MARCHING_BASE
#define _MARCHING_BASE

class marchingBase{
public:
	virtual GLvoid MarchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);
	GLvoid MarchingCubes(){
		GLint iX, iY, iZ;
		for (iX = 0; iX < mDataSetSize; iX++)
		for (iY = 0; iY < mDataSetSize; iY++)
		for (iZ = 0; iZ < mDataSetSize; iZ++)
		{
			MarchCube(iX*fStepSize, iY*fStepSize, iZ*fStepSize, fStepSize);
		}
	}

protected:
	GLint	mDataSetSize = 16;
	GLfloat fStepSize = 1.0 / mDataSetSize;
};


#endif // _MARCHING_BASE