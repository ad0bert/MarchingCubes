#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QColorDialog>
#include <gl/GLU.h>
#include "fileHandler.h"
#include "marchingcubes.h"

class Tetrahedron : public QGLWidget
{
    Q_OBJECT

public:
    Tetrahedron(QWidget *parent = 0);
    void setObject(std::vector<TRIANGLE> *object);
    void updateUI();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
private:
    void draw();
    int faceAtPosition(const QPoint &pos);
	void qNormalizeAngle(int &angle);
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;
    std::vector<TRIANGLE> mObject;
};

#endif
