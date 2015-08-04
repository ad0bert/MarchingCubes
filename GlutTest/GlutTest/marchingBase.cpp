#include "marchingBase.h"
#include <glut.h>

GLvoid marchingBase::MarchingCubes(){
	GLint iX, iY, iZ;
	for (iX = 0; iX < h->iDataSetSize; iX++)
	for (iY = 0; iY < h->iDataSetSize; iY++)
	for (iZ = 0; iZ < h->iDataSetSize; iZ++)
	{
		MarchCube(iX*h->fStepSize, iY*h->fStepSize, iZ*h->fStepSize, h->fStepSize);
	}
}

GLfloat marchingBase::fGetOffset(GLfloat fValue1, GLfloat fValue2, GLfloat fValueDesired)
{
	GLdouble fDelta = fValue2 - fValue1;

	if (fDelta == 0.0)
	{
		return 0.5;
	}
	return (fValueDesired - fValue1) / fDelta;
}

//vGetColor generates a color from a given position and normal of a point
GLvoid marchingBase::vGetColor(GLvector &rfColor, GLvector &rfPosition, GLvector &rfNormal)
{
	GLfloat fX = rfNormal.fX;
	GLfloat fY = rfNormal.fY;
	GLfloat fZ = rfNormal.fZ;
	rfColor.fX = (fX > 0.0 ? fX : 0.0) + (fY < 0.0 ? -0.5*fY : 0.0) + (fZ < 0.0 ? -0.5*fZ : 0.0);
	rfColor.fY = (fY > 0.0 ? fY : 0.0) + (fZ < 0.0 ? -0.5*fZ : 0.0) + (fX < 0.0 ? -0.5*fX : 0.0);
	rfColor.fZ = (fZ > 0.0 ? fZ : 0.0) + (fX < 0.0 ? -0.5*fX : 0.0) + (fY < 0.0 ? -0.5*fY : 0.0);
}

//vGetNormal() finds the gradient of the scalar field at a point
//This gradient can be used as a very accurate vertx normal for lighting calculations
GLvoid marchingBase::vGetNormal(GLvector &rfNormal, GLfloat fX, GLfloat fY, GLfloat fZ)
{
	rfNormal.fX = h->fSample(fX - 0.01, fY, fZ) - h->fSample(fX + 0.01, fY, fZ);
	rfNormal.fY = h->fSample(fX, fY - 0.01, fZ) - h->fSample(fX, fY + 0.01, fZ);
	rfNormal.fZ = h->fSample(fX, fY, fZ - 0.01) - h->fSample(fX, fY, fZ + 0.01);
	vNormalizeVector(rfNormal, rfNormal);
}

GLvoid marchingBase::vNormalizeVector(GLvector &rfVectorResult, GLvector &rfVectorSource)
{
	GLfloat fOldLength;
	GLfloat fScale;

	fOldLength = sqrtf((rfVectorSource.fX * rfVectorSource.fX) +
		(rfVectorSource.fY * rfVectorSource.fY) +
		(rfVectorSource.fZ * rfVectorSource.fZ));

	if (fOldLength == 0.0)
	{
		rfVectorResult.fX = rfVectorSource.fX;
		rfVectorResult.fY = rfVectorSource.fY;
		rfVectorResult.fZ = rfVectorSource.fZ;
	}
	else
	{
		fScale = 1.0 / fOldLength;
		rfVectorResult.fX = rfVectorSource.fX*fScale;
		rfVectorResult.fY = rfVectorSource.fY*fScale;
		rfVectorResult.fZ = rfVectorSource.fZ*fScale;
	}
}