#ifndef PECAS
#define PECAS

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float pecas_J1[12][3];
extern float pecas_J2[12][3];

extern int damas_J1[12];
extern int damas_J2[12];

bool ehUmaDama(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
               float pecas[12][3], int damas[12])
{
    float posicaoXSeletor = seletorX + seletorX_aux;
    float posicaoYSeletor = seletorY + seletorY_aux;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecas[i][0] && posicaoYSeletor == pecas[i][1]) // SE EXISTE UMA PEÇA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (damas[i] == 1) // SE ESSA PEÇA É UMA DAMA.
            {
                return true;
            }
        }
    }

    return false;
}

bool temPecaNaCasa(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                   float pecas[12][3])
{
    float posicaoXSeletor = seletorX + seletorX_aux;
    float posicaoYSeletor = seletorY + seletorY_aux;

    for (int i = 0; i < 12; i++)
    {
        if (posicaoXSeletor == pecas[i][0] && posicaoYSeletor == pecas[i][1]) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            return true;
        }
    }

    return false;
}

bool podeMoverParaCima(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 11.0f; //  11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // <
    {
        // (seletorX - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX - 0.5f) + seletorY_aux < yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }
    else if (seletorX == 11.5f) // >
    {
        // (seletorX - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX - 0.5f) + seletorY_aux > yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }

    return true;
}

bool podeMoverParaBaixo(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 4.0f; //  4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // >
    {
        // (seletorX - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX - 0.5f) + seletorY_aux > yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }
    else if (seletorX == 11.5f) // <
    {
        // (seletorX - 0.5f) REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PECAS.
        if (!((seletorX - 0.5f) + seletorY_aux < yA3Casa)) // SE NÃO HÁ MAIS CASAS POSSÍVEIS PARA A PECA CONTINUAR 'SUBINDO' NO TABULEIRO.
        {
            return false;
        }
    }

    return true;
}

bool podeMoverParaEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                                   float pecas_J1[12][3], float pecas_J2[12][3])
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // >
    {
        if ((seletorX - 0.5f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX == 11.5f) // <
    {
        if ((seletorX - 0.5f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeMoverParaEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                                   float pecas_J1[12][3], float pecas_J2[12][3])
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 4.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 11.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // >
    {
        if ((seletorX - 0.5f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX == 11.5f) // <
    {
        if ((seletorX - 0.5f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeMoverParaDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                                  float pecas_J1[12][3], float pecas_J2[12][3])
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 11.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 4.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // <
    {
        if ((seletorX - 0.5f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX == 11.5f) // >
    {
        if ((seletorX - 0.5f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

bool podeMoverParaDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                                  float pecas_J1[12][3], float pecas_J2[12][3])
{
    float yA3Casa;

    if (seletorX == 4.5f)
    {
        yA3Casa = 11.0f; // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }
    else if (seletorX == 11.5f)
    {
        yA3Casa = 4.0f; // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
    }

    if (seletorX == 4.5f) // <
    {
        if ((seletorX - 0.5f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }
    else if (seletorX == 11.5f) // >
    {
        if ((seletorX - 0.5f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                return true;
            }
        }
    }

    return false;
}

void opcaoSeletorEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX == 4.5f)
    {
        somaX = 3.5f;
        somaY = 5.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX == 11.5f)
    {
        somaX = 12.5f;
        somaY = 10.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX == 4.5f)
    {
        somaX = 3.5f;
        somaY = 3.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX == 11.5f)
    {
        somaX = 12.5f;
        somaY = 12.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX == 4.5f)
    {
        somaX = 5.5f;
        somaY = 5.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX == 11.5f)
    {
        somaX = 10.5f;
        somaY = 10.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX == 4.5f)
    {
        somaX = 5.5f;
        somaY = 3.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX == 11.5f)
    {
        somaX = 10.5f;
        somaY = 12.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void seletorDePeca(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                   float pecas_J1[12][3], float pecas_J2[12][3], int damas[12], bool pecaEstaSelecionada)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    bool condicaoTemPecaNaCasa;
    bool condicaoEhUmaDama;

    if (seletorX == 4.5f)
    {
        somaX = 4.5f;
        somaY = 4.5f;
        corR = 0;
        corB = 40;

        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas);
    }
    else if (seletorX == 11.5f)
    {
        somaX = 11.5f;
        somaY = 11.5f;
        corR = 40;
        corB = 0;

        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas);
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.
    glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();

    if (pecaEstaSelecionada)
    {
        if (condicaoTemPecaNaCasa) // SE EXISTE UMA PECA NO LOCAL QUE O SELETOR SELECIONOU.
        {
            if (podeMoverParaCima(seletorX_aux, seletorY_aux, seletorX, seletorY))
            {
                if (podeMoverParaEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                {
                    opcaoSeletorEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY);
                }

                if (podeMoverParaDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                {
                    opcaoSeletorDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY);
                }
            }

            if (condicaoEhUmaDama) // SE A PEÇA É UMA DAMA.
            {
                if (podeMoverParaBaixo(seletorX_aux, seletorY_aux, seletorX, seletorY))
                {
                    if (podeMoverParaEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                    {
                        opcaoSeletorEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY);
                    }

                    if (podeMoverParaDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                    {
                        opcaoSeletorDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY);
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

        glTranslatef(pecas_J1[i][0], pecas_J1[i][1], pecas_J1[i][2]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(100, 100, 255, 255, GL_FILL);

        glPopMatrix();
    }

    // JOGADOR 2
    for (int i = 0; i < 12; i++)
    {
        glPushMatrix();

        glTranslatef(pecas_J2[i][0], pecas_J2[i][1], pecas_J2[i][2]);
        glScalef(0.4f, 0.4f, 0.125f);
        cilindro(255, 100, 100, 255, GL_FILL);

        glPopMatrix();
    }
}

#endif
