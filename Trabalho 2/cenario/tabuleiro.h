#ifndef TABULEIRO
#define TABULEIRO

#include "../formasGeometricas/cubo.h"
#include "../iluminacao/luz.h"
#include <glm/vec3.hpp>

Cubo baseTabuleiro_forma;
Cubo casaBranca_forma;
Cubo casaPreta_forma;

extern int baseTabuleiro_textura;
extern int casaBranca_textura;
extern int casaPreta_textura;

void baseTabuleiro(Luz &luz)
{
    glPushMatrix();

    glTranslatef(3.0f, 3.0f, 1.0f);
    glScalef(10.0f, 10.0f, 0.5f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    baseTabuleiro_forma.desenha(luz, baseTabuleiro_textura);
    baseTabuleiro_forma.setCor(255, 255, 255);
    glPopMatrix();
}

void casas(Luz &luz)
{
    float x[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
    float y[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};

    int corR[2] = {255, 255};
    int corG[2] = {255, 255};
    int corB[2] = {255, 255};

    bool aux = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            glPushMatrix();

            glTranslatef(x[i], y[j], 1.5f);
            glScalef(1.0f, 1.0f, 0.125f);
            glTranslatef(0.5f, 0.5f, 0.0f);

            if (aux)
            {
                casaBranca_forma.desenha(luz, casaBranca_textura);
                casaBranca_forma.setCor(corR[aux], corG[aux], corB[aux]);
            }
            else
            {
                casaPreta_forma.desenha(luz, casaPreta_textura);
                casaPreta_forma.setCor(corR[aux], corG[aux], corB[aux]);
            }

            glPopMatrix();

            aux += -1;
        }
        aux += -1;
    }
}

void tabuleiro(Luz &luz)
{
    baseTabuleiro(luz);
    casas(luz);
}

#endif
