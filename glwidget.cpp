
#include "glwidget.h"
#include <math.h>

#include <QDebug>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

const GLfloat PI180 = M_PI / 180;

GLWidget::GLWidget(QWidget* parent/*= 0*/) : QGLWidget(parent) {
    glparams = new GLParams(1, 0, 0, 0, -90, 0, 0);
    earth = new Earth(0.6f, 40, 40);
    plane = new Plane(0.04f, Qt::blue);

    //flights.append(new Flight(plane, new Place(1.8, 0.7), new Place(4, 1)));

    for (int i = 0; i < 20; i++) {
        flights.append(new Flight(plane,
                                  new Place(randomFloat(0, M_PI * 2), randomFloat(0, M_PI * 2)),
                                  new Place(randomFloat(0, M_PI * 2), randomFloat(0, M_PI * 2)),
                                  rand() % 500));
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));
    timer->start(30);
}

GLWidget::~GLWidget() {
    makeCurrent();
    glDeleteTextures(1, textureID);
}

float GLWidget::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void GLWidget::genTextures() {
   QImage image;
   image.load(QCoreApplication::applicationDirPath() + "/world_map.jpg");
   image = QGLWidget::convertToGLFormat(image);
   glGenTextures(1, textureID);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image.width(), (GLsizei)image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void GLWidget::initializeGL() {
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    genTextures();
    //glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(glparams->getNSca(), glparams->getNSca(), glparams->getNSca());
    glTranslatef(glparams->getXTra(), glparams->getYTra(), glparams->getZTra());
    glRotatef(glparams->getXRot(), 1.0f, 0.0f, 0.0f);
    glRotatef(glparams->getYRot(), 0.0f, 1.0f, 0.0f);
    glRotatef(glparams->getZRot(), 0.0f, 0.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);

    earth->draw();

    glDisable(GL_TEXTURE_2D);

    qglColor(plane->getColor());
    for (int i = 0; i < flights.size(); i++) {
        flights[i]->draw(glparams);
    }
}

void GLWidget::resizeGL(int nWidth, int nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (GLfloat)nHeight / (GLfloat)nWidth;
    if (nWidth >= nHeight)
       glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 10.0);
    else
       glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 10.0);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void GLWidget::mousePressEvent(QMouseEvent* e) {
    ptrMousePosition = e->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* e) {
    GLfloat xTra = glparams->getXTra();
    GLfloat yTra = glparams->getYTra();
    if (e->buttons() & Qt::MiddleButton) {
        xTra += (GLfloat)(e->pos().x() - ptrMousePosition.x()) / (GLfloat)400;
        yTra -= (GLfloat)(e->pos().y() - ptrMousePosition.y()) / (GLfloat)400;
    }
    glparams->setXTra(xTra);
    glparams->setYTra(yTra);
    GLfloat xRot = glparams->getXRot();
    GLfloat zRot = glparams->getZRot();
    if (e->buttons() & Qt::LeftButton) {
        GLfloat t = xRot + 180 /*/ nSca*/ * (GLfloat)(e->y() - ptrMousePosition.y()) / height();
        xRot = t;
        zRot += 180 /*/ nSca*/ * (GLfloat)(e->x() - ptrMousePosition.x()) / width();
    }
    glparams->setXRot(xRot);
    glparams->setZRot(zRot);
    ptrMousePosition = e->pos();
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *e) {
    GLfloat nSca = glparams->getNSca();
    e->delta() > 0 ? nSca *= 1.1f : nSca /= 1.1f;
    glparams->setNSca(nSca);
    updateGL();
}

void GLWidget::change() {
    updateGL();
}

void GLWidget::start() {
    for (int i = 0; i < flights.size(); i++) {
        flights[i]->start();
    }
}
