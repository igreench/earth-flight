#ifndef PLANE_H
#define PLANE_H

#include <QtOpenGL>

class Plane {
public:
    Plane(GLfloat side, QColor color);

    QColor getColor();
    void setPos(GLfloat x, GLfloat y, GLfloat z);
    void setRot(GLfloat xRot, GLfloat yRot, GLfloat zRot);
    GLfloat getSide();

private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat side;
    QColor color;
};

#endif // PLANE_H
