#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

#include "earth.h"
#include "place.h"
#include "plane.h"
#include "flight.h"
#include "glparams.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void start();
    float randomFloat(float a, float b);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

protected slots:
    void change();

private:
    void setupViewport(int width, int height);
    void genTextures();

    QPoint ptrMousePosition;
    GLuint textureID[1];
    Plane *plane;
    Earth *earth;
    //Flight *flight;
    QList <Flight *> flights;
    GLParams *glparams;
};

#endif // GLWIDGET_H
