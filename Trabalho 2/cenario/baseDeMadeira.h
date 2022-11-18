#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../formasGeometricas/cubo2.h"
#include "../iluminacao/luz.h"
#include <glm/vec3.hpp>

Cubo base;

extern int baseMadeira;

void baseDeMadeira(Luz &luz)
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);

    base.desenha(luz, baseMadeira);
    base.setCor(255, 255, 255);

    glPopMatrix();
}

#endif
