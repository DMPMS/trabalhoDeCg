#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../formasGeometricas/cubo2.h"
#include "../iluminacao/luz.h"
#include <glm/vec3.hpp>

Cubo base;

void baseDeMadeira(Luz &luz)
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    // cubo(150, 75, 0, 255, GL_FILL);
    // cubo(0, 0, 0, 255, GL_LINE);
    base.desenha(luz);
    base.setCor(150, 75, 255);

    glPopMatrix();
}

#endif
