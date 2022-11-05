#ifndef TABULEIRO
#define TABULEIRO

#include "../cubo.h"

void baseTabuleiro()
{
    glPushMatrix();

    glTranslatef(3.0f, 3.0f, 1.0f);
    glScalef(10.0f, 10.0f, 0.5f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    cubo(30, 30, 30, 255, GL_FILL);
    cubo(0, 0, 0, 255, GL_LINE);

    glPopMatrix();
}

void escaques()
{
    float x[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
    float y[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};

    int corR[2] = {99, 231};
    int corG[2] = {53, 209};
    int corB[2] = {28, 133};

    bool aux = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            glPushMatrix();

            glTranslatef(x[i], y[j], 1.5f);
            glScalef(1.0f, 1.0f, 0.125f);
            glTranslatef(0.5f, 0.5f, 0.0f);
            cubo(corR[aux], corG[aux], corB[aux], 255, GL_FILL);
            cubo(0, 0, 0, 255, GL_LINE);

            glPopMatrix();

            aux += -1;
        }
        aux += -1;
    }
}

void tabuleiro()
{
    baseTabuleiro();
    escaques();
}

#endif
