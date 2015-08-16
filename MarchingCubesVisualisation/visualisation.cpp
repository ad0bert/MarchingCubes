#include "Visualisation.h"

Visualisation::Visualisation(QWidget *parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    rotationX = 0.0;
    rotationY = 0.0;
	rotationZ = 0.0;
	mScale = 0.01;
}

void Visualisation::updateUI(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->clearMask();
    updateGL();
}

void Visualisation::setWiring(bool enable){
    if (enable)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    updateGL();
}

void Visualisation::scaleObject(){
	for (auto &obj : mObject) {
		for (int j = 0; j < 3; ++j) {
			obj.p[j].x = obj.p[j].x - 100;
			obj.p[j].y = obj.p[j].y - 100;
			obj.p[j].z = obj.p[j].z - 100;
		}
	}
}

void Visualisation::setObject(std::vector<TRIANGLE> *object){
    mObject.clear();
    updateGL();
    mObject = *object;
	scaleObject();
}

void Visualisation::initializeGL()
{
	qglClearColor(Qt::black);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRONT_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void Visualisation::resizeGL(int width, int height)
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

void Visualisation::qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

void Visualisation::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationX) {
		rotationX = angle;
		updateGL();
	}
}

void Visualisation::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationY) {
		rotationY = angle;
		updateGL();
	}
}

void Visualisation::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != rotationZ) {
		rotationZ = angle;
		updateGL();
	}
}

void Visualisation::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(rotationX / 16.0, 1.0, 0.0, 0.0);
	glRotatef(rotationY / 16.0, 0.0, 1.0, 0.0);
	glRotatef(rotationZ / 16.0, 0.0, 0.0, 1.0);
	glScalef(mScale, mScale, mScale); // scale the matrix
    draw();
}

void Visualisation::draw()
{
    drawAll();
}


void Visualisation::drawAll(){
#pragma omp parallel
	for (auto obj : mObject) {		
		glBegin(GL_TRIANGLES);
		glNormal3f(obj.n.x, obj.n.y, obj.n.z);
        for (int j = 0; j < 3; ++j) {		
			glVertex3f(obj.p[j].x, obj.p[j].y, obj.p[j].z);
        }
        glEnd();
    }
}

void Visualisation::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Visualisation::wheelEvent(QWheelEvent *event)
{
	if (event->delta() < 0){
		mScale -= 0.001;
	}
	else{
		mScale += 0.001;
	}
	updateGL();
}

void Visualisation::mouseMoveEvent(QMouseEvent *event)
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