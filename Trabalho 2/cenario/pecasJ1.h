#ifndef PECASJ1
#define PECASJ1

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float pecasJ1X[12];
extern float pecasJ1Y[12];
extern float pecasJ1Z[12];

extern float pecasJ2X[12];
extern float pecasJ2Y[12];
extern float pecasJ2Z[12];

extern int damasJ1[12];
extern int damasJ2[12];

bool ehUmaDamaJ1(float seletorJ1X, float seletorJ1Y)
{
    float posicaoXSeletor = 4.5f + seletorJ1X;
    float posicaoYSeletor = 4.5f + seletorJ1Y;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasJ1X[i] && posicaoYSeletor == pecasJ1Y[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (damasJ1[i] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

bool temPecaNaCasaJ1(float seletorJ1X, float seletorJ1Y)
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

bool podeIrPraCimaJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (!(4.0f + seletorJ1Y < 11.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
    {
        return false;
    }

    return true;
}

bool podeIrPraBaixoJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1.
    if (!(4.0f + seletorJ1Y > 4.0f))
    {
        return false;
    }

    return true;
}

bool podeIrPraEsquerdaSuperiorJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ1(seletorJ1X - 1.0f, seletorJ1Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraEsquerdaInferiorJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ1(seletorJ1X - 1.0f, seletorJ1Y - 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireitaSuperiorJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ1(seletorJ1X + 1.0f, seletorJ1Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireitaInferiorJ1(float seletorJ1X, float seletorJ1Y)
{
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (4.0f + seletorJ1X < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ1(seletorJ1X + 1.0f, seletorJ1Y - 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

void opcaoSeletorEsquerdaSuperiorJ1(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(3.5f + seletorJ1X, 5.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorEsquerdaInferiorJ1(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(3.5f + seletorJ1X, 3.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaSuperiorJ1(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(5.5f + seletorJ1X, 5.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaInferiorJ1(float seletorJ1X, float seletorJ1Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(5.5f + seletorJ1X, 3.5f + seletorJ1Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(0, 0, 40, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDePecaJ1(float seletorJ1X, float seletorJ1Y, bool pecaSelecionada)
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
        if (temPecaNaCasaJ1(seletorJ1X, seletorJ1Y)) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeIrPraCimaJ1(seletorJ1X, seletorJ1Y))
            {
                if (podeIrPraEsquerdaSuperiorJ1(seletorJ1X, seletorJ1Y))
                {
                    opcaoSeletorEsquerdaSuperiorJ1(seletorJ1X, seletorJ1Y);
                }

                if (podeIrPraDireitaSuperiorJ1(seletorJ1X, seletorJ1Y))
                {
                    opcaoSeletorDireitaSuperiorJ1(seletorJ1X, seletorJ1Y);
                }
            }

            if (ehUmaDamaJ1(seletorJ1X, seletorJ1Y))
            {
                if (podeIrPraBaixoJ1(seletorJ1X, seletorJ1Y))
                {
                    if (podeIrPraEsquerdaInferiorJ1(seletorJ1X, seletorJ1Y))
                    {
                        opcaoSeletorEsquerdaInferiorJ1(seletorJ1X, seletorJ1Y);
                    }

                    if (podeIrPraDireitaInferiorJ1(seletorJ1X, seletorJ1Y))
                    {
                        opcaoSeletorDireitaInferiorJ1(seletorJ1X, seletorJ1Y);
                    }
                }
            }
        }
    }
}

void pecasJ1()
{
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(pecasJ1X[i], pecasJ1Y[i], pecasJ1Z[i]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(100, 100, 255, 255, GL_FILL);

        glPopMatrix();
    }
}

#endif
