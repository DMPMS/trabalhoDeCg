#ifndef DAMAS
#define DAMAS

#include "../cubo.h"
#include "../cilindro.h"

extern float damasJ1X[12];
extern float damasJ1Y[12];
extern float damasJ1Z[12];

bool temDama(float seletorX, float seletorY)
{
    float posicaoXSeletor = 4.5f + seletorX;
    float posicaoYSeletor = 4.5f + seletorY;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == damasJ1X[i] && posicaoYSeletor == damasJ1Y[i]) // SE EXISTE UMA DAMA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraEsquerda(float seletorX, float seletorY)
{
    if (temDama(seletorX, seletorY)) // SE EXISTE UMA DAMA NO LOCAL QUE O SELETOR SELECIONOU.
    {
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8.
        if (!(4.0f + seletorY < 11.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A DAMA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }

        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a.
        if (4.0f + seletorX > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temDama(seletorX - 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeIrPraDireita(float seletorX, float seletorY)
{
    if (temDama(seletorX, seletorY)) // SE EXISTE UMA DAMA NO LOCAL QUE O SELETOR SELECIONOU.
    {
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8.
        if (!(4.0f + seletorY < 11.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A DAMA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }

        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a.
        if (4.0f + seletorX < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temDama(seletorX + 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

void seletorDeDama(float seletorX, float seletorY, bool damaSelecionada)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO E NÃO FICAR PISCANDO
    glTranslatef(4.5f + seletorX, 4.5f + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (damaSelecionada) // SE A DAMA ESTÁ SELECIONADA.
    {
        if (temDama(seletorX, seletorY)) // SE EXISTE UMA DAMA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8.
            if (4.0f + seletorY < 11.0f) // VERIFICA SE AINDA HÁ CASAS POSSÍVEIS PARA A DAMA CONTINUAR 'SUBINDO' NO TABULEIRO.
            {
                // OPÇÃO DE MOVIMENDO PARA ESQUERDA
                // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
                // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a.
                if (4.0f + seletorX > 4.0f) // PARA NÃO MOSTRAR OPÇÕES FORA DO TABULEIRO.
                {
                    if (!temDama(seletorX - 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
                    {
                        glPushMatrix();

                        glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO E NÃO FICAR PISCANDO
                        glTranslatef(3.5f + seletorX, 5.5f + seletorY, 1.625f);
                        glScalef(1.0f, 1.0f, 0.125f);
                        cubo(40, 0, 0, 150, GL_FILL);
                        cubo(0, 0, 0, 150, GL_LINE);

                        glPopMatrix();
                    }
                }

                // OPÇÃO DE MOVIMENTO PARA DIREITA
                // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
                // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h.
                if (4.0f + seletorX < 11.0f) // PARA NÃO MOSTRAR OPÇÕES FORA DO TABULEIRO.
                {
                    if (!temDama(seletorX + 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
                    {
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
    }
}

void damas()
{
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(damasJ1X[i], damasJ1Y[i], damasJ1Z[i]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(100, 100, 255, 255, GL_FILL);

        glPopMatrix();
    }
}

#endif
