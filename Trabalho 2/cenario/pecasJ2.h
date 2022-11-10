#ifndef PECASJ2
#define PECASJ2

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float pecasJ2X[12];
extern float pecasJ2Y[12];
extern float pecasJ1Z[12];

extern float pecasJ2X[12];
extern float pecasJ2Y[12];
extern float pecasJ2Z[12];

extern int damasJ1[12];
extern int damasJ2[12];

bool ehUmaDamaJ2(float seletorJ2X, float seletorJ2Y)
{
    float posicaoXSeletor = 11.5f + seletorJ2X;
    float posicaoYSeletor = 11.5f + seletorJ2Y;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasJ2X[i] && posicaoYSeletor == pecasJ2Y[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (damasJ2[i] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

bool temPecaNaCasaJ2(float seletorJ2X, float seletorJ2Y)
{
    float posicaoXSeletor = 11.5f + seletorJ2X;
    float posicaoYSeletor = 11.5f + seletorJ2Y;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasJ2X[i] && posicaoYSeletor == pecasJ2Y[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraCimaJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (!(11.0f + seletorJ2Y > 4.0f)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
    {
        return false;
    }

    return true;
}

bool podeIrPraBaixoJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
    // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (!(11.0f + seletorJ2Y < 11.0f))
    {
        return false;
    }

    return true;
}

bool podeIrPraEsquerdaSuperiorJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (11.0f + seletorJ2X < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ2(seletorJ2X + 1.0f, seletorJ2Y - 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraEsquerdaInferiorJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (11.0f + seletorJ2X < 11.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ2(seletorJ2X + 1.0f, seletorJ2Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireitaSuperiorJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (11.0f + seletorJ2X > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ2(seletorJ2X - 1.0f, seletorJ2Y - 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraDireitaInferiorJ2(float seletorJ2X, float seletorJ2Y)
{
    // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PECAS.
    // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    if (11.0f + seletorJ2X > 4.0f) // SE FOR UMA CASA DO TABULEIRO.
    {
        if (!temPecaNaCasaJ2(seletorJ2X - 1.0f, seletorJ2Y + 1.0f)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
        {
            return true;
        }
    }

    return false;
}

void opcaoSeletorEsquerdaSuperiorJ2(float seletorJ2X, float seletorJ2Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(12.5f + seletorJ2X, 10.5f + seletorJ2Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorEsquerdaInferiorJ2(float seletorJ2X, float seletorJ2Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(12.5f + seletorJ2X, 12.5f + seletorJ2Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaSuperiorJ2(float seletorJ2X, float seletorJ2Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(10.5f + seletorJ2X, 10.5f + seletorJ2Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaInferiorJ2(float seletorJ2X, float seletorJ2Y)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(10.5f + seletorJ2X, 12.5f + seletorJ2Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDePecaJ2(float seletorJ2X, float seletorJ2Y, bool pecaSelecionada)
{
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(11.5f + seletorJ2X, 11.5f + seletorJ2Y, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(40, 0, 0, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (pecaSelecionada)
    {
        if (temPecaNaCasaJ2(seletorJ2X, seletorJ2Y)) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeIrPraCimaJ2(seletorJ2X, seletorJ2Y))
            {
                if (podeIrPraEsquerdaSuperiorJ2(seletorJ2X, seletorJ2Y))
                {
                    opcaoSeletorEsquerdaSuperiorJ2(seletorJ2X, seletorJ2Y);
                }

                if (podeIrPraDireitaSuperiorJ2(seletorJ2X, seletorJ2Y))
                {
                    opcaoSeletorDireitaSuperiorJ2(seletorJ2X, seletorJ2Y);
                }
            }

            if (ehUmaDamaJ2(seletorJ2X, seletorJ2Y))
            {
                if (podeIrPraBaixoJ2(seletorJ2X, seletorJ2Y))
                {
                    if (podeIrPraEsquerdaInferiorJ2(seletorJ2X, seletorJ2Y))
                    {
                        opcaoSeletorEsquerdaInferiorJ2(seletorJ2X, seletorJ2Y);
                    }

                    if (podeIrPraDireitaInferiorJ2(seletorJ2X, seletorJ2Y))
                    {
                        opcaoSeletorDireitaInferiorJ2(seletorJ2X, seletorJ2Y);
                    }
                }
            }
        }
    }
}

void pecasJ2()
{
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(pecasJ2X[i], pecasJ2Y[i], pecasJ2Z[i]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(255, 100, 100, 255, GL_FILL);

        glPopMatrix();
    }
}

#endif
