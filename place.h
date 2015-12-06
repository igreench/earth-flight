#ifndef PLACE_H
#define PLACE_H

#include <QtOpenGL>

class Place {
public:
    Place(GLfloat angleHor, GLfloat angleVer);

    GLfloat getAngleHor();
    GLfloat getAngleVer();

    void setAngleHor(GLfloat angleHor);
    void setAngleVer(GLfloat angleVer);

private:
    GLfloat angleHor;
    GLfloat angleVer;
};

#endif // PLACE_H
