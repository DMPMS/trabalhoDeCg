#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../formasGeometricas/cubo.h"

extern int texID[6];

void baseDeMadeira()
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    cubo(255, 255, 255, 255, GL_FILL, texID[3]);

    glPopMatrix();
}

#endif
