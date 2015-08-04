#ifndef _HELPER_H
#define _HELPER_H

#include <glut.h>
#include <cmath>

struct GLvector
{
	GLfloat fX;
	GLfloat fY;
	GLfloat fZ;
};

enum sample{ sample1, sample2, sample3 };

class helper{
public: 
	sample    sam = sample1;
	GLfloat   fTargetValue = 48.0;
	GLfloat   fTime = 0.0;
	GLvector  sSourcePoint[3];
	GLint     iDataSetSize = 16;
	GLfloat   fStepSize = 1.0 / iDataSetSize;


	GLfloat	  fSample(GLfloat fX, GLfloat fY, GLfloat fZ){
		switch (sam){
		case sample1:
			return fSample1(fX, fY, fZ);
		case sample2:
			return fSample2(fX, fY, fZ);
		case sample3:
			return fSample3(fX, fY, fZ);
		default:
			return fSample1(fX, fY, fZ);
		}
	}
	

private:
	//fSample1 finds the distance of (fX, fY, fZ) from three moving points
	GLfloat fSample1(GLfloat fX, GLfloat fY, GLfloat fZ)
	{
		GLdouble fResult = 0.0;
		GLdouble fDx, fDy, fDz;
		fDx = fX - sSourcePoint[0].fX;
		fDy = fY - sSourcePoint[0].fY;
		fDz = fZ - sSourcePoint[0].fZ;
		fResult += 0.5 / (fDx*fDx + fDy*fDy + fDz*fDz);

		fDx = fX - sSourcePoint[1].fX;
		fDy = fY - sSourcePoint[1].fY;
		fDz = fZ - sSourcePoint[1].fZ;
		fResult += 1.0 / (fDx*fDx + fDy*fDy + fDz*fDz);

		fDx = fX - sSourcePoint[2].fX;
		fDy = fY - sSourcePoint[2].fY;
		fDz = fZ - sSourcePoint[2].fZ;
		fResult += 1.5 / (fDx*fDx + fDy*fDy + fDz*fDz);

		return fResult;
	}

	//fSample2 finds the distance of (fX, fY, fZ) from three moving lines
	GLfloat fSample2(GLfloat fX, GLfloat fY, GLfloat fZ)
	{
		GLdouble fResult = 0.0;
		GLdouble fDx, fDy, fDz;
		fDx = fX - sSourcePoint[0].fX;
		fDy = fY - sSourcePoint[0].fY;
		fResult += 0.5 / (fDx*fDx + fDy*fDy);

		fDx = fX - sSourcePoint[1].fX;
		fDz = fZ - sSourcePoint[1].fZ;
		fResult += 0.75 / (fDx*fDx + fDz*fDz);

		fDy = fY - sSourcePoint[2].fY;
		fDz = fZ - sSourcePoint[2].fZ;
		fResult += 1.0 / (fDy*fDy + fDz*fDz);

		return fResult;
	}


	//fSample2 defines a height field by plugging the distance from the center into the sin and cos functions
	GLfloat fSample3(GLfloat fX, GLfloat fY, GLfloat fZ)
	{
		GLfloat fHeight = 20.0*(fTime + sqrt((0.5 - fX)*(0.5 - fX) + (0.5 - fY)*(0.5 - fY)));
		fHeight = 1.5 + 0.1*(sinf(fHeight) + cosf(fHeight));
		GLdouble fResult = (fHeight - fZ)*50.0;

		return fResult;
	}

};

//These tables are used so that everything can be done in little loops that you can look at all at once
// rather than in pages and pages of unrolled code.


static const GLfloat afAmbientWhite[] = { 0.25, 0.25, 0.25, 1.00 };
static const GLfloat afAmbientRed[] = { 0.25, 0.00, 0.00, 1.00 };
static const GLfloat afAmbientGreen[] = { 0.00, 0.25, 0.00, 1.00 };
static const GLfloat afAmbientBlue[] = { 0.00, 0.00, 0.25, 1.00 };
static const GLfloat afDiffuseWhite[] = { 0.75, 0.75, 0.75, 1.00 };
static const GLfloat afDiffuseRed[] = { 0.75, 0.00, 0.00, 1.00 };
static const GLfloat afDiffuseGreen[] = { 0.00, 0.75, 0.00, 1.00 };
static const GLfloat afDiffuseBlue[] = { 0.00, 0.00, 0.75, 1.00 };
static const GLfloat afSpecularWhite[] = { 1.00, 1.00, 1.00, 1.00 };
static const GLfloat afSpecularRed[] = { 1.00, 0.25, 0.25, 1.00 };
static const GLfloat afSpecularGreen[] = { 0.25, 1.00, 0.25, 1.00 };
static const GLfloat afSpecularBlue[] = { 0.25, 0.25, 1.00, 1.00 };


//a2fVertexOffset lists the positions, relative to vertex0, of each of the 8 vertices of a cube
static const GLfloat a2fVertexOffset[8][3] =
{
	{ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 }
};



#endif // _HELPER_H