#include "tetrahedron.h"

Tetrahedron::Tetrahedron(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    rotationX = 0.0;
    rotationY = 0.0;
	rotationZ = 0.0;
	mSize = 100;
}

void Tetrahedron::updateUI(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->clearMask();
    updateGL();
}

void Tetrahedron::setWiring(bool enable){
    if (enable)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
		updateGL();
	}
}

void Tetrahedron::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationY) {
		rotationY = angle;
		updateGL();
	}
}

void Tetrahedron::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationZ) {
		rotationZ = angle;
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
    drawAll();
}


void Tetrahedron::drawAll(){
    for (int i = 0; i < mObject.size(); ++i) {
        glBegin(GL_TRIANGLES);
        glNormal3f(mObject[i].n.x, mObject[i].n.y, mObject[i].n.z);
        for (int j = 0; j < 3; ++j) {
			glVertex3f(mObject.at(i).p[j].x / mSize - 1, mObject.at(i).p[j].y / mSize - 1,
				mObject.at(i).p[j].z / mSize - 1);
        }
        glEnd();
    }
}

void Tetrahedron::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Tetrahedron::wheelEvent(QWheelEvent *event)
{
	 mSize += event->delta()/100;
	 updateGL();
}

void Tetrahedron::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(rotationX + 4 * dy);
		setYRotation(rotationY + 4 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(rotationX + 4 * dy);
		setZRotation(rotationZ + 4 * dx);
	}

	lastPos = event->pos();
}