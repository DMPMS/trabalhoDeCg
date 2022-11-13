#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../formasGeometricas/cubo.h"

void baseDeMadeira(int *texId)
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    cubo(150, 75, 0, 255, GL_FILL, texId[0]);
    cubo(0, 0, 0, 255, GL_LINE, 0);

    glPopMatrix();
}

#endif
