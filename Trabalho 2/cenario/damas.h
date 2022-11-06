#ifndef DAMAS
#define DAMAS

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float damasJ1X[12];
extern float damasJ1Y[12];
extern float damasJ1Z[12];

extern float damasJ2X[12];
extern float damasJ2Y[12];
extern float damasJ2Z[12];

bool temDamaNaCasa(float seletorX, float seletorY)
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

bool podeIrPraCima(float seletorX, float seletorY)
{
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA). 
    if (!(4.0f + seletorY < 11.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A DAMA CONTINUAR 'SUBINDO' NO TABULEIRO.
    {
        return false;
    }

    return true;
}

bool podeIrPraEsquerda(float seletorX, float seletorY)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorX > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temDamaNaCasa(seletorX - 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireita(float seletorX, float seletorY)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorX < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temDamaNaCasa(seletorX + 1.0f, seletorY + 1.0f)) // SE NÃO EXISTE OUTRA DAMA NA OPÇÃO DE MOVIMENTO DA DAMA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

void moverDamaParaEsquerda(float seletorX, float seletorY)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(3.5f + seletorX, 5.5f + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void moverDamaParaDireita(float seletorX, float seletorY)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(5.5f + seletorX, 5.5f + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDeDama(float seletorX, float seletorY, bool damaSelecionada)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(4.5f + seletorX, 4.5f + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (damaSelecionada)
    {
        if (temDamaNaCasa(seletorX, seletorY)) // SE EXISTE UMA DAMA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeIrPraCima(seletorX, seletorY))
            {
                if (podeIrPraEsquerda(seletorX, seletorY))
                {
                    moverDamaParaEsquerda(seletorX, seletorY);
                }

                if (podeIrPraDireita(seletorX, seletorY))
                {
                    moverDamaParaDireita(seletorX, seletorY);
                }
            }
        }
    }
}

void damas()
{
    // JOGADOR 1
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(damasJ1X[i], damasJ1Y[i], damasJ1Z[i]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(100, 100, 255, 255, GL_FILL);

        glPopMatrix();
    }

    // JOGADOR 2
    // for (int i = 0; i < 12; i++)
    // {
    //     glPushMatrix();

    //     glTranslatef(damasJ2X[i], damasJ2Y[i], damasJ2Z[i]);
    //     glScalef(0.4f, 0.4f, 0.125f);
    //     cilindro(255, 100, 100, 255, GL_FILL);

    //     glPopMatrix();
    // }
}

#endif
