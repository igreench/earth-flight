#include "plane.h"

Plane::Plane(GLfloat side, QColor color) {
    this->x = 1;
    this->y = 0;
    this->z = 0;
    this->xRot = 0;
    this->yRot = 0;
    this->zRot = 0;
    this->side = side;
    this->color = color;
}

QColor Plane::getColor() {
    return color;
}

void Plane::setPos(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->y = z;
    //qDebug() << x << " " << y << " " << z;
}

void Plane::setRot(GLfloat xRot, GLfloat yRot, GLfloat zRot) {
    this->xRot = xRot;
    this->yRot = yRot;
    this->zRot = zRot;
}

GLfloat Plane::getSide() {
    return side;
}
