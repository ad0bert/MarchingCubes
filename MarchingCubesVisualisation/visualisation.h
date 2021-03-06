#ifndef Visualisation_H
#define Visualisation_H

#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QColorDialog>
#include <gl/GLU.h>
#include "fileHandler.h"
#include "marchingcubes.h"

class Visualisation : public QGLWidget
{
    Q_OBJECT

public:
    Visualisation(QWidget *parent = 0);
    void setObject(std::vector<TRIANGLE> *object);
    void setWiring(bool enable);
    void updateUI();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
private:
    void draw();
	void qNormalizeAngle(int &angle);
    void drawSlice();
    void drawAll();
	void scaleObject();
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;
    std::vector<TRIANGLE> mObject;
	GLfloat mScale;
};

#endif
