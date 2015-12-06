#include "glparams.h"

GLParams::GLParams(GLfloat nSca, GLfloat xTra, GLfloat yTra, GLfloat zTra,
         GLfloat xRot, GLfloat yRot, GLfloat zRot) {
    this->nSca = nSca;
    this->xTra = xTra;
    this->yTra = yTra;
    this->zTra = zTra;
    this->xRot = xRot;
    this->yRot = yRot;
    this->zRot = zRot;
}

GLParams::GLParams(GLParams *glparams) {
    this->nSca = glparams->nSca;
    this->xTra = glparams->xTra;
    this->yTra = glparams->yTra;
    this->zTra = glparams->zTra;
    this->xRot = glparams->xRot;
    this->yRot = glparams->yRot;
    this->zRot = glparams->zRot;
}

GLfloat GLParams::getNSca() {
    return nSca;
}

GLfloat GLParams::getXTra() {
    return xTra;
}

GLfloat GLParams::getYTra() {
    return yTra;
}

GLfloat GLParams::getZTra() {
    return zTra;
}

GLfloat GLParams::getXRot() {
    return xRot;
}

GLfloat GLParams::getYRot() {
    return yRot;
}

GLfloat GLParams::getZRot() {
    return zRot;
}

void GLParams::setNSca(GLfloat value) {
    nSca = value;
}

void GLParams::setXTra(GLfloat value) {
    xTra = value;
}

void GLParams::setYTra(GLfloat value) {
    yTra = value;
}

void GLParams::setZTra(GLfloat value) {
    zTra = value;
}

void GLParams::setXRot(GLfloat value) {
    xRot = value;
}

void GLParams::setYRot(GLfloat value) {
    yRot = value;
}

void GLParams::setZRot(GLfloat value) {
    zRot = value;
}
