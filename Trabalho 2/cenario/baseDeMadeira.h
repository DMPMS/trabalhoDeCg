#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../cubo.h"

void baseDeMadeira()
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    cubo(150, 75, 0, 255, GL_FILL);
    cubo(0, 0, 0, 255, GL_LINE);

    glPopMatrix();
}

#endif