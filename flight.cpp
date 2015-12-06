#include "flight.h"

#include <QDebug>

Flight::Flight(Plane *plane, Place *from, Place *to) {
    this->plane = plane;
    this->from = from;
    this->to = to;

    radius = 0.6f;
    lineSlices = 20;

    init();

    currentTime = 0;
    timeFlight = 400;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));
}

Flight::Flight(Plane *plane, Place *from, Place *to, int timeFlight) {
    this->plane = plane;
    this->from = from;
    this->to = to;

    radius = 0.6f;
    lineSlices = 20;

    init();

    currentTime = 0;
    this->timeFlight = timeFlight;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(change()));
}

void Flight::init() {
    vecFrom = QVector3D(radius * qCos(from->getAngleHor()) * qCos(from->getAngleVer()),
                        radius * qSin(from->getAngleHor()) * qCos(from->getAngleVer()),
                        radius * qSin(from->getAngleVer()));

    vecTo = QVector3D(radius * qCos(to->getAngleHor()) * qCos(to->getAngleVer()),
                      radius * qSin(to->getAngleHor()) * qCos(to->getAngleVer()),
                      radius * qSin(to->getAngleVer()));

    normal = QVector3D::normal(vecFrom, vecTo);

    aHor = -qAcos(QVector2D::dotProduct(QVector2D(normal.x(), normal.y()), QVector2D(1, 0)) /
                     QVector2D(normal.x(), normal.y()).length());

    aVer = qAcos(QVector2D::dotProduct(QVector2D(1, 0), QVector2D(normal.z(),
                                                 normal.y() * qSin(aHor) + normal.x() * qCos(aHor))) /
                 QVector2D(normal.z(), normal.y() * qSin(aHor) + normal.x() * qCos(aHor)).length());

    vect0 = QVector3D(
                radius * 4 * qCos(aHor) * qCos(aVer - M_PI / 2),
                radius * 4 * qSin(aHor) * qCos(aVer - M_PI / 2),
                radius * 4 * qSin(aVer - M_PI / 2));
}

void Flight::start() {
    timer->start(30);
}

void Flight::change() {
    QVector3D pt = getPoint((double)currentTime / timeFlight);
    plane->setPos(pt.x(), pt.y(), pt.z());
    currentTime++;
    if (currentTime == timeFlight) {
        from->setAngleHor(to->getAngleHor());
        from->setAngleVer(to->getAngleVer());
        to->setAngleHor(randomFloat(0, M_PI * 2));
        to->setAngleVer(randomFloat(0, M_PI * 2));
        currentTime = 0;
        init();
        //timer->stop();
    }
}

Place Flight::getFrom() {
    return *from;
}

Place Flight::getTo() {
    return *to;
}

QVector3D Flight::getPoint(double x) {
    double k = x;
    if (x < 0 || x > 1) {
        k = 0;
    }
    double r = radius / 2;

    double a1  = 0.28f + qAcos( QVector3D::dotProduct(vect0, vecFrom) / (vect0.length() * vecFrom.length()));
    double a2  = qAcos( QVector3D::dotProduct(vecFrom, vecTo) / (vecFrom.length() * vecTo.length()));

    double a = a1 + a2 * k;

    return QVector3D((radius + pow(r, 2) - pow((x - 0.5) * r * 2, 2)) * qCos(a),
                     (radius + pow(r, 2) - pow((x - 0.5) * r * 2, 2)) * qSin(a),
                     0);
}

void Flight::draw(GLParams *glparams) {

    glLoadIdentity();
    glScalef(glparams->getNSca(), glparams->getNSca(), glparams->getNSca());
    glTranslatef(glparams->getXTra(), glparams->getYTra(), glparams->getZTra());
    glRotatef(glparams->getXRot(), 1.0f, 0.0f, 0.0f);
    glRotatef(glparams->getYRot(), 0.0f, 1.0f, 0.0f);
    glRotatef(glparams->getZRot(), 0.0f, 0.0f, 1.0f);

    glLineWidth(2);
    glColor3f(0.5f, 0.5f, 0.5f);

    glLoadIdentity();
    glScalef(glparams->getNSca(), glparams->getNSca(), glparams->getNSca());
    glTranslatef(glparams->getXTra(), glparams->getYTra(), glparams->getZTra());
    glRotatef(glparams->getXRot(), 1.0f, 0.0f, 0.0f);
    glRotatef(glparams->getZRot() + aHor * 180 / M_PI, 0.0f, 0.0f, 1.0f);
    glRotatef(glparams->getYRot() + aVer * 180 / M_PI, 0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
    for (int i = 0; i < lineSlices; i++) {

        if ((double)i / lineSlices <= (double)currentTime / timeFlight &&
                (double)(i + 1) / lineSlices >= (double)currentTime / timeFlight) {
            QVector3D pt1 = getPoint((double)i / lineSlices);
            QVector3D pt2 = getPoint((double)currentTime / timeFlight);
            QVector3D pt3 = getPoint((double)(i + 1) / lineSlices);

            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(pt1.x(), pt1.y(), pt1.z());
            glVertex3f(pt2.x(), pt2.y(), pt2.z());

            if (i % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex3f(pt2.x(), pt2.y(), pt2.z());
                glVertex3f(pt3.x(), pt3.y(), pt3.z());
            }
        } else {
            if ((double)i / lineSlices < (double)currentTime / timeFlight) {
                glColor3f(1.0f, 0.0f, 0.0f);

                QVector3D pt1 = getPoint((double)i / lineSlices);
                QVector3D pt2 = getPoint((double)(i + 1) / lineSlices);
                glVertex3f(pt1.x(), pt1.y(), pt1.z());
                glVertex3f(pt2.x(), pt2.y(), pt2.z());
            } else {
                if (i % 2 == 0) {
                    glColor3f(1.0f, 1.0f, 1.0f);

                    QVector3D pt1 = getPoint((double)i / lineSlices);
                    QVector3D pt2 = getPoint((double)(i + 1) / lineSlices);
                    glVertex3f(pt1.x(), pt1.y(), pt1.z());
                    glVertex3f(pt2.x(), pt2.y(), pt2.z());
                }
            }

        }
    }

    glEnd();

    QVector3D pt = getPoint((double)currentTime / timeFlight);

    pt = pt * 1.01f;
    glColor3f(0.0f, 0.0f, 1.0f);
    if (from->getAngleHor() <= to->getAngleHor()) {//?
        glBegin(GL_TRIANGLES);
        glVertex3f(pt.x(), pt.y(), pt.z());
        glVertex3f(pt.x() - plane->getSide() * qCos(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.y() - plane->getSide() * qSin(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.z() - plane->getSide() / 2);
        glVertex3f(pt.x() - plane->getSide() * qCos(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.y() - plane->getSide() * qSin(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.z() + plane->getSide() / 2);
        glEnd();
    } else {
        glBegin(GL_TRIANGLES);
        glVertex3f(pt.x(), pt.y(), pt.z());
        glVertex3f(pt.x() + plane->getSide() * qCos(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.y() + plane->getSide() * qSin(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.z() - plane->getSide() / 2);
        glVertex3f(pt.x() + plane->getSide() * qCos(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.y() + plane->getSide() * qSin(qAtan2(pt.y(), pt.x()) + M_PI / 2),
                   pt.z() + plane->getSide() / 2);
        glEnd();
    }
}

void Flight::setFrom(Place from) {
    this->from->setAngleHor(from.getAngleHor());
    this->from->setAngleVer(from.getAngleVer());
}

void Flight::setTo(Place to) {
    this->to->setAngleHor(to.getAngleHor());
    this->to->setAngleVer(to.getAngleVer());
}

float Flight::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
