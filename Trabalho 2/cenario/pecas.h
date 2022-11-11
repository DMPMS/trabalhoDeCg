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

extern int damasJ1[12];
extern int damasJ2[12];

bool ehUmaDama(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
               float pecasX[12], float pecasY[12], int damas[12])
{
    float posicaoXSeletor = seletorX_pos + seletorX;
    float posicaoYSeletor = seletorY_pos + seletorY;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasX[i] && posicaoYSeletor == pecasY[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (damas[i] == 1)
            {
                return true;
            }
        }
    }

    return false;
}

bool temPecaNaCasa(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                   float pecasX[12], float pecasY[12])
{
    float posicaoXSeletor = seletorX_pos + seletorX;
    float posicaoYSeletor = seletorY_pos + seletorY;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecasX[i] && posicaoYSeletor == pecasY[i]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            return true;
        }
    }

    return false;
}

bool podeIrPraCima(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 11.0f; //  11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // <
    {
        // (seletorX_pos - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX_pos - 0.5f) + seletorY < yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }
    else if (seletorX_pos == 11.5f) // >
    {
        // (seletorX_pos - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX_pos - 0.5f) + seletorY > yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }

    return true;
}

bool podeIrPraBaixo(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 4.0f; //  4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // >
    {
        // (seletorX_pos - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX_pos - 0.5f) + seletorY > yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }
    else if (seletorX_pos == 11.5f) // <
    {
        // (seletorX_pos - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX_pos - 0.5f) + seletorY < yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }

    return true;
}

bool podeIrPraEsquerdaSuperior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                               float pecasX[12], float pecasY[12])
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // >
    {
        if ((seletorX_pos - 0.5f) + seletorX > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX - 1.0f, seletorY + 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX_pos == 11.5f) // <
    {
        if ((seletorX_pos - 0.5f) + seletorX < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX + 1.0f, seletorY - 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeIrPraEsquerdaInferior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                               float pecasX[12], float pecasY[12])
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // >
    {
        if ((seletorX_pos - 0.5f) + seletorX > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX - 1.0f, seletorY - 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX_pos == 11.5f) // <
    {
        if ((seletorX_pos - 0.5f) + seletorX < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX + 1.0f, seletorY + 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeIrPraDireitaSuperior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                              float pecasX[12], float pecasY[12])
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 11.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 4.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // <
    {
        if ((seletorX_pos - 0.5f) + seletorX < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX + 1.0f, seletorY + 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX_pos == 11.5f) // >
    {
        if ((seletorX_pos - 0.5f) + seletorX > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX - 1.0f, seletorY - 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeIrPraDireitaInferior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                              float pecasX[12], float pecasY[12])
{
    float yA3Casa;

    if (seletorX_pos == 4.5f)
    {
        yA3Casa = 11.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX_pos == 11.5f)
    {
        yA3Casa = 4.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX_pos == 4.5f) // <
    {
        if ((seletorX_pos - 0.5f) + seletorX < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX + 1.0f, seletorY - 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX_pos == 11.5f) // >
    {
        if ((seletorX_pos - 0.5f) + seletorX > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX - 1.0f, seletorY + 1.0f, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

void opcaoSeletorEsquerdaSuperior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX_pos == 4.5f)
    {
        somaX = 3.5f;
        somaY = 5.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX_pos == 11.5f)
    {
        somaX = 12.5f;
        somaY = 10.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX, somaY + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorEsquerdaInferior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX_pos == 4.5f)
    {
        somaX = 3.5f;
        somaY = 3.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX_pos == 11.5f)
    {
        somaX = 12.5f;
        somaY = 12.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX, somaY + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaSuperior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX_pos == 4.5f)
    {
        somaX = 5.5f;
        somaY = 5.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX_pos == 11.5f)
    {
        somaX = 10.5f;
        somaY = 10.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX, somaY + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaInferior(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX_pos == 4.5f)
    {
        somaX = 5.5f;
        somaY = 3.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX_pos == 11.5f)
    {
        somaX = 10.5f;
        somaY = 12.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX, somaY + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDePeca(float seletorX, float seletorY, float seletorX_pos, float seletorY_pos,
                   float pecasX[12], float pecasY[12], int damas[12], bool pecaSelecionada)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX_pos == 4.5f)
    {
        somaX = 4.5f;
        somaY = 4.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX_pos == 11.5f)
    {
        somaX = 11.5f;
        somaY = 11.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX, somaY + seletorY, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (pecaSelecionada)
    {
        if (temPecaNaCasa(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY)) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeIrPraCima(seletorX, seletorY, seletorX_pos, seletorY_pos))
            {
                if (podeIrPraEsquerdaSuperior(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY))
                {
                    opcaoSeletorEsquerdaSuperior(seletorX, seletorY, seletorX_pos, seletorY_pos);
                }

                if (podeIrPraDireitaSuperior(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY))
                {
                    opcaoSeletorDireitaSuperior(seletorX, seletorY, seletorX_pos, seletorY_pos);
                }
            }

            if (ehUmaDama(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY, damas))
            {
                if (podeIrPraBaixo(seletorX, seletorY, seletorX_pos, seletorY_pos))
                {
                    if (podeIrPraEsquerdaInferior(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY))
                    {
                        opcaoSeletorEsquerdaInferior(seletorX, seletorY, seletorX_pos, seletorY_pos);
                    }

                    if (podeIrPraDireitaInferior(seletorX, seletorY, seletorX_pos, seletorY_pos, pecasX, pecasY))
                    {
                        opcaoSeletorDireitaInferior(seletorX, seletorY, seletorX_pos, seletorY_pos);
                    }
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
