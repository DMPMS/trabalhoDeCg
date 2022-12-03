#ifndef BASEDEMADEIRA
#define BASEDEMADEIRA

#include "../formasGeometricas/cubo.h"
#include "../iluminacao/luz.h"
#include <glm/vec3.hpp>

Cubo baseDeMadeira_forma;

extern int baseDeMadeira_textura;

void baseDeMadeira(Luz &luz)
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);

    baseDeMadeira_forma.desenha(luz, baseDeMadeira_textura);
    baseDeMadeira_forma.setCor(255, 255, 255);

    glPopMatrix();
}

#endif
