#ifndef DAMAS
#define DAMAS

#include "../cubo.h"
#include "../cilindro.h"

void seletorDeDama(float seletorX, float seletorY, bool pecaSelecionada)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO E NÃO FICAR PISCANDO
    glTranslatef(4.5f + seletorX, 4.5f + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (pecaSelecionada)
    {
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
        // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER ESCAQUE DA LINHA 8.
        if (4.0f + seletorY < 11.0f)
        {

            // ESQUERDA
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER ESCAQUE DA COLUNA a.
            if (4.0f + seletorX > 4.0f) // PARA NÃO MOSTRAR OPÇÕES FORA DO TABULEIRO.
            {
                glPushMatrix();

                glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO E NÃO FICAR PISCANDO
                glTranslatef(3.5f + seletorX, 5.5f + seletorY, 1.625f);
                glScalef(1.0f, 1.0f, 0.125f);
                cubo(40, 0, 0, 150, GL_FILL);
                cubo(0, 0, 0, 150, GL_LINE);

                glPopMatrix();
            }

            // DIREITA
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER ESCAQUE DA COLUNA h.
            if (4.0f + seletorX < 11.0f)
            { // PARA NÃO MOSTRAR OPÇÕES FORA DO TABULEIRO.

                glPushMatrix();

                glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO E NÃO FICAR PISCANDO
                glTranslatef(5.5f + seletorX, 5.5f + seletorY, 1.625f);
                glScalef(1.0f, 1.0f, 0.125f);
                cubo(40, 0, 0, 150, GL_FILL);
                cubo(0, 0, 0, 150, GL_LINE);

                glPopMatrix();
            }
        }
    }
}

void dama()
{
    glPushMatrix();

    glTranslatef(5.5f, 4.5f, 1.625f);
    glScalef(0.4f, 0.4f, 0.125f);
    cilindro(100, 100, 255, 255, GL_FILL);

    glPopMatrix();
}

#endif
