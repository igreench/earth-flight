#ifndef FLIGHT_H
#define FLIGHT_H

#include <QtOpenGL>

#include "place.h"
#include "plane.h"
#include "glparams.h"

class Flight : public QObject {
    Q_OBJECT

public:
    Flight(Plane *plane, Place *from, Place *to);
    Flight(Plane *plane, Place *from, Place *to, int timeFlight);

    void init();
    void start();

    Place getFrom();
    Place getTo();

    void setFrom(Place from);
    void setTo(Place to);

    void draw(GLParams *glparams);
    QVector3D getPoint(double x);

    float randomFloat(float a, float b);

private slots:
    void change();

private:
    Plane *plane;
    Place *from;
    Place *to;
    QVector3D vecFrom;
    QVector3D vecTo;
    GLfloat radius;
    int lineSlices;

    QTimer *timer;
    int currentTime;
    int timeFlight;

    QVector3D normal;
    QVector3D vect0;
    GLfloat aHor;
    GLfloat aVer;
};

#endif // FLIGHT_H
