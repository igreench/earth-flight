#include "earth.h"

Earth::Earth(GLfloat x, GLfloat y, GLfloat z,
      GLfloat radius, GLfloat numHSlices, GLfloat numVSlices) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->numHSlices = numHSlices;
    this->numVSlices = numVSlices;
}

Earth::Earth(GLfloat radius, GLfloat numHSlices, GLfloat numVSlices) {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->radius = radius;
    this->numHSlices = numHSlices;
    this->numVSlices = numVSlices;
}

void Earth::draw() {
    glBegin(GL_QUADS);
    for (int i = 0; i < numVSlices; i++) {
        for (int j = 0; j < numHSlices; j++) {
            glTexCoord2f(1.0f * j / numHSlices, 1.0f - 1.0f * i / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * j * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       y + radius * qSin(M_PI * j * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       z + radius * qCos(M_PI * i / numVSlices));
            glTexCoord2f(1.0f * (j + 1) / numHSlices, 1.0f - 1.0f * i / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       y + radius * qSin(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * i / numVSlices),
                       z + radius * qCos(M_PI * i / numVSlices));
            glTexCoord2f(1.0f * (j + 1) / numHSlices, 1.0f - 1.0f * (i + 1) / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       y + radius * qSin(M_PI * (j + 1) * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       z + radius * qCos(M_PI * (i + 1) / numVSlices));
            glTexCoord2f(1.0f * j / numHSlices, 1.0f - 1.0f * (i + 1) / numVSlices);
            glVertex3f(x + radius * qCos(M_PI * j * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       y + radius * qSin(M_PI * j * 2 / numHSlices) * qSin(M_PI * (i + 1) / numVSlices),
                       z + radius * qCos(M_PI * (i + 1) / numVSlices));
        }
    }
    glEnd();
}
