#ifndef EARTH_H
#define EARTH_H

#include <QtOpenGL>

class Earth {
public:
    Earth(GLfloat x, GLfloat y, GLfloat z,
          GLfloat radius, GLfloat numHSlices, GLfloat numVSlices);

    Earth(GLfloat radius, GLfloat numHSlices, GLfloat numVSlices);

    void draw();

private:
    GLfloat x;
    GLfloat y;
    GLfloat z;

    GLfloat radius;
    GLfloat numHSlices;
    GLfloat numVSlices;
};

#endif // EARTH_H
