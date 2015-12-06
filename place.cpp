#include "place.h"

Place::Place(GLfloat angleHor, GLfloat angleVer) {
    this->angleHor = angleHor;
    this->angleVer = angleVer;
}

GLfloat Place::getAngleHor() {
    return angleHor;
}

GLfloat Place::getAngleVer() {
    return angleVer;
}

void Place::setAngleHor(GLfloat angleHor) {
    this->angleHor = angleHor;
}

void Place::setAngleVer(GLfloat angleVer) {
    this->angleVer = angleVer;
}
