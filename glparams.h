#ifndef GLPARAMS_H
#define GLPARAMS_H

#include <QtOpenGL>

class GLParams {
public:
    GLParams(GLfloat nSca, GLfloat xTra, GLfloat yTra, GLfloat zTra,
             GLfloat xRot, GLfloat yRot, GLfloat zRot);
    GLParams(GLParams *glparams);

    GLfloat getNSca();
    GLfloat getXTra();
    GLfloat getYTra();
    GLfloat getZTra();
    GLfloat getXRot();
    GLfloat getYRot();
    GLfloat getZRot();

    void setNSca(GLfloat value);
    void setXTra(GLfloat value);
    void setYTra(GLfloat value);
    void setZTra(GLfloat value);
    void setXRot(GLfloat value);
    void setYRot(GLfloat value);
    void setZRot(GLfloat value);

private:
    GLfloat nSca;
    GLfloat xTra;
    GLfloat yTra;
    GLfloat zTra;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
};

#endif // GLPARAMS_H
