//
// Marching Cubes Example Program 
// by Cory Bloyd (corysama@yahoo.com)
//
// A simple, portable and complete implementation of the Marching Cubes
// and Marching Tetrahedrons algorithms in a single source file.
// There are many ways that this code could be made faster, but the 
// intent is for the code to be easy to understand.
//
// For a description of the algorithm go to
// http://astronomy.swin.edu.au/pbourke/modelling/polygonise/
//
// This code is public domain.
//

#include "stdio.h"
//This program requires the OpenGL and GLUT libraries
// You can obtain them for free from http://www.opengl.org
#include "glut.h"
#include "helper.h"
#include "marchingBase.h"
#include "marchingCubes.h"
#include "marchingTetrahedron.h"

GLenum    ePolygonMode = GL_FILL;
GLboolean bSpin = true;
GLboolean bMove = true;
GLboolean bLight = true;

marchingBase *vMarchCube = nullptr;
marchingCubes *vMarchCube1 = nullptr;
marchingTetrahedron *vMarchCube2 = nullptr;
helper *h = nullptr;

void vIdle();
void vDrawScene();
void vResize(GLsizei, GLsizei);
void vKeyboard(unsigned char cKey, int iX, int iY);
void vSpecial(int iKey, int iX, int iY);

GLvoid vPrintHelp();
GLvoid vSetTime(GLfloat fTime);

void main(int argc, char **argv)
{
	h = new helper();
	vMarchCube1 = new marchingCubes(h);
	vMarchCube2 = new marchingTetrahedron(h);

	vMarchCube = vMarchCube1;

	GLfloat afPropertiesAmbient[] = { 0.50, 0.50, 0.50, 1.00 };
	GLfloat afPropertiesDiffuse[] = { 0.75, 0.75, 0.75, 1.00 };
	GLfloat afPropertiesSpecular[] = { 1.00, 1.00, 1.00, 1.00 };

	GLsizei iWidth = 640.0;
	GLsizei iHeight = 480.0;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(iWidth, iHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Marching Cubes");
	glutDisplayFunc(vDrawScene);
	glutIdleFunc(vIdle);
	glutReshapeFunc(vResize);
	glutKeyboardFunc(vKeyboard);
	glutSpecialFunc(vSpecial);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, ePolygonMode);

	glLightfv(GL_LIGHT0, GL_AMBIENT, afPropertiesAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, afPropertiesDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, afPropertiesSpecular);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

	glEnable(GL_LIGHT0);

	glMaterialfv(GL_BACK, GL_AMBIENT, afAmbientGreen);
	glMaterialfv(GL_BACK, GL_DIFFUSE, afDiffuseGreen);
	glMaterialfv(GL_FRONT, GL_AMBIENT, afAmbientBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, afDiffuseBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, afSpecularWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

	vResize(iWidth, iHeight);

	vPrintHelp();
	glutMainLoop();
	delete vMarchCube1;
	delete vMarchCube2;
}

GLvoid vPrintHelp()
{
	printf("Marching Cubes Example by Cory Bloyd (dejaspaminacan@my-deja.com)\n\n");

	printf("+/-  increase/decrease sample density\n");
	printf("PageUp/PageDown  increase/decrease surface value\n");
	printf("s  change sample function\n");
	printf("c  toggle marching cubes / marching tetrahedrons\n");
	printf("w  wireframe on/off\n");
	printf("l  toggle lighting / color-by-normal\n");
	printf("Home  spin scene on/off\n");
	printf("End  source point animation on/off\n");
}


void vResize(GLsizei iWidth, GLsizei iHeight)
{
	GLfloat fAspect, fHalfWorldSize = (1.4142135623730950488016887242097 / 2);

	glViewport(0, 0, iWidth, iHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (iWidth <= iHeight)
	{
		fAspect = (GLfloat)iHeight / (GLfloat)iWidth;
		glOrtho(-fHalfWorldSize, fHalfWorldSize, -fHalfWorldSize*fAspect,
			fHalfWorldSize*fAspect, -10 * fHalfWorldSize, 10 * fHalfWorldSize);
	}
	else
	{
		fAspect = (GLfloat)iWidth / (GLfloat)iHeight;
		glOrtho(-fHalfWorldSize*fAspect, fHalfWorldSize*fAspect, -fHalfWorldSize,
			fHalfWorldSize, -10 * fHalfWorldSize, 10 * fHalfWorldSize);
	}

	glMatrixMode(GL_MODELVIEW);
}

void vKeyboard(unsigned char cKey, int iX, int iY)
{
	switch (cKey)
	{
	case 'w':
	{
				if (ePolygonMode == GL_LINE)
				{
					ePolygonMode = GL_FILL;
				}
				else
				{
					ePolygonMode = GL_LINE;
				}
				glPolygonMode(GL_FRONT_AND_BACK, ePolygonMode);
	} break;
	case '+':
	case '=':
	{
				++h->iDataSetSize;
				h->fStepSize = 1.0 / h->iDataSetSize;
	} break;
	case '-':
	{
				if (h->iDataSetSize > 1)
				{
					--h->iDataSetSize;
					h->fStepSize = 1.0 / h->iDataSetSize;
				}
	} break;
	case 'c':
	{
				if (vMarchCube == vMarchCube1)
				{
					vMarchCube = vMarchCube2;//Use Marching Tetrahedrons
				}
				else
				{
					vMarchCube = vMarchCube1;//Use Marching Cubes
				}
	} break;
	case 's':
	{
				if (h->sam == sample1)
				{
					h->sam = sample2;
				}
				else if (h->sam == sample2)
				{
					h->sam = sample3;
				}
				else
				{
					h->sam = sample1;
				}
	} break;
	case 'l':
	{
				if (bLight)
				{
					glDisable(GL_LIGHTING);//use vertex colors
				}
				else
				{
					glEnable(GL_LIGHTING);//use lit material color
				}

				bLight = !bLight;
	};
	}
}


void vSpecial(int iKey, int iX, int iY)
{
	switch (iKey)
	{
	case GLUT_KEY_PAGE_UP:
	{
							 if (h->fTargetValue < 1000.0)
							 {
								 h->fTargetValue *= 1.1;
							 }
	} break;
	case GLUT_KEY_PAGE_DOWN:
	{
							   if (h->fTargetValue > 1.0)
							   {
								   h->fTargetValue /= 1.1;
							   }
	} break;
	case GLUT_KEY_HOME:
	{
						  bSpin = !bSpin;
	} break;
	case GLUT_KEY_END:
	{
						 bMove = !bMove;
	} break;
	}
}

void vIdle()
{
	glutPostRedisplay();
}

void vDrawScene()
{
	static GLfloat fPitch = 0.0;
	static GLfloat fYaw = 0.0;
	static GLfloat fTime = 0.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	if (bSpin)
	{
		fPitch += 4.0;
		fYaw += 2.5;
	}
	if (bMove)
	{
		fTime += 0.025;
	}

	vSetTime(fTime);

	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(-fPitch, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(fYaw, 0.0, 0.0, 1.0);

	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1.0);
	glPopAttrib();


	glPushMatrix();
	glTranslatef(-0.5, -0.5, -0.5);
	glBegin(GL_TRIANGLES);
	vMarchCube->MarchingCubes();
	glEnd();
	glPopMatrix();


	glPopMatrix();

	glutSwapBuffers();
}

//Generate a sample data set.  fSample1(), fSample2() and fSample3() define three scalar fields whose
// values vary by the X,Y and Z coordinates and by the fTime value set by vSetTime()
GLvoid vSetTime(GLfloat fNewTime)
{
	GLfloat fOffset;
	GLint iSourceNum;

	for (iSourceNum = 0; iSourceNum < 3; iSourceNum++)
	{
		h->sSourcePoint[iSourceNum].fX = 0.5;
		h->sSourcePoint[iSourceNum].fY = 0.5;
		h->sSourcePoint[iSourceNum].fZ = 0.5;
	}

	h->fTime = fNewTime;
	fOffset = 1.0 + sinf(h->fTime);
	h->sSourcePoint[0].fX *= fOffset;
	h->sSourcePoint[1].fY *= fOffset;
	h->sSourcePoint[2].fZ *= fOffset;
}