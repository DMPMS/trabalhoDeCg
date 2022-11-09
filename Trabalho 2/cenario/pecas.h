#ifndef PECAS
#define PECAS

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float pecasJ1X[12];
extern float pecasJ1Y[12];
extern float pecasJ1Z[12];

extern float pecasJ2X[12];
extern float pecasJ2Y[12];
extern float pecasJ2Z[12];

bool temPecaNaCasa(float seletorJ1X, float seletorJ1Y)
{
    float posicaoXSeletor = 4.5f + seletorJ1X;
    float posicaoYSeletor = 4.5f + seletorJ1Y;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasJ1X[i] && posicaoYSeletor == pecasJ1Y[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraCima(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA). 
    if (!(4.0f + seletorJ1Y < 11.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
    {
        return false;
    }

    return true;
}

bool podeIrPraEsquerda(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasa(seletorJ1X - 1.0f, seletorJ1Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireita(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasa(seletorJ1X + 1.0f, seletorJ1Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

void moverPecaParaEsquerda(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(3.5f + seletorJ1X, 5.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void moverPecaParaDireita(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(5.5f + seletorJ1X, 5.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDePeca(float seletorJ1X, float seletorJ1Y, bool pecaSelecionada)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(4.5f + seletorJ1X, 4.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (pecaSelecionada)
    {
        if (temPecaNaCasa(seletorJ1X, seletorJ1Y)) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeIrPraCima(seletorJ1X, seletorJ1Y))
            {
                if (podeIrPraEsquerda(seletorJ1X, seletorJ1Y))
                {
                    moverPecaParaEsquerda(seletorJ1X, seletorJ1Y);
                }

                if (podeIrPraDireita(seletorJ1X, seletorJ1Y))
                {
                    moverPecaParaDireita(seletorJ1X, seletorJ1Y);
                }
            }
        }
    }
}

void pecas()
{
    // JOGADOR 1
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(pecasJ1X[i], pecasJ1Y[i], pecasJ1Z[i]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(100, 100, 255, 255, GL_FILL);

        glPopMatrix();
    }

    // JOGADOR 2
    // for (int i = 0; i < 12; i++)
    // {
    //     glPushMatrix();

    //     glTranslatef(pecasJ2X[i], pecasJ2Y[i], pecasJ2Z[i]);
    //     glScalef(0.4f, 0.4f, 0.125f);
    //     cilindro(255, 100, 100, 255, GL_FILL);

    //     glPopMatrix();
    // }
}

#endif
