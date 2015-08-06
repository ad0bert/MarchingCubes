#include "tetrahedron.h"

Tetrahedron::Tetrahedron(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    rotationX = 0.0;
    rotationY = 0.0;
	rotationZ = 0.0;
}

void Tetrahedron::updateUI(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->clearMask();
    updateGL();
}

void Tetrahedron::setObject(std::vector<TRIANGLE> *object){
    mObject.clear();
    updateGL();
    mObject = *object;
}

void Tetrahedron::initializeGL()
{
	qglClearColor(Qt::black);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void Tetrahedron::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifdef QT_OPENGL_ES_1
	glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
	glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
	glMatrixMode(GL_MODELVIEW);
}

void Tetrahedron::qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void Tetrahedron::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationX) {
		rotationX = angle;
		//emit xRotationChanged(angle);
		updateGL();
	}
}

void Tetrahedron::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationY) {
		rotationY = angle;
		//emit yRotationChanged(angle);
		updateGL();
	}
}

void Tetrahedron::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationZ) {
		rotationZ = angle;
		//emit zRotationChanged(angle);
		updateGL();
	}
}

void Tetrahedron::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(rotationX / 16.0, 1.0, 0.0, 0.0);
	glRotatef(rotationY / 16.0, 0.0, 1.0, 0.0);
	glRotatef(rotationZ / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void Tetrahedron::draw()
{
	qglColor(Qt::red);
	
    for (int i = 0; i < mObject.size(); ++i) {
		glBegin(GL_TRIANGLES);
		glNormal3f(mObject[i].n[0].x, mObject[i].n[0].y, mObject[i].n[0].z);
        for (int j = 0; j < 3; ++j) {			
			glVertex3f(mObject.at(i).p[j].x/100, mObject.at(i).p[j].y/100,
				mObject.at(i).p[j].z/100);
        }
        glEnd();
    }
}

void Tetrahedron::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Tetrahedron::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(rotationX + 8 * dy);
		setYRotation(rotationY + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(rotationX + 8 * dy);
		setZRotation(rotationZ + 8 * dx);
	}

	lastPos = event->pos();
}

void Tetrahedron::mouseDoubleClickEvent(QMouseEvent *event)
{
    int face = faceAtPosition(event->pos());
    if (face != -1) {
        QColor color = QColorDialog::getColor(faceColors[face], this);
        if (color.isValid()) {
            faceColors[face] = color;
            updateGL();
        }
    }
}

int Tetrahedron::faceAtPosition(const QPoint &pos)
{
    const int MaxSize = 512;
    GLuint buffer[MaxSize];
    GLint viewport[4];

    makeCurrent();

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()),
        5.0, 5.0, viewport);
    GLfloat x = GLfloat(width()) / height();
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}
