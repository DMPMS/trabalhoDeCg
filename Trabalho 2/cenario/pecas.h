#ifndef PECAS
#define PECAS

#include "../formasGeometricas/cubo.h"
#include "../formasGeometricas/cilindro.h"

extern float pecas_J1[12][3];
extern float pecas_J2[12][3];

extern int damas_J1[12];
extern int damas_J2[12];

extern char moverPeca_direcao;
extern bool moverPeca_animacao;
extern bool vaiComerPeca;

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

void moverParaEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], bool pecaEstaSelecionada)
{
    bool condicaoTemPecaNaCasa;

    if (seletorX == 4.5f)
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
    }
    else
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (podeMoverParaCima(seletorX_aux, seletorY_aux, seletorX, seletorY) &&
        podeMoverParaEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = false;
    }
}

void moverParaDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                              float pecas_J1[12][3], float pecas_J2[12][3], bool pecaEstaSelecionada)
{
    bool condicaoTemPecaNaCasa;

    if (seletorX == 4.5f)
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
    }
    else
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (podeMoverParaCima(seletorX_aux, seletorY_aux, seletorX, seletorY) &&
        podeMoverParaDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = false;
    }
}

void moverParaEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], int damas[12], bool pecaEstaSelecionada)
{
    bool condicaoTemPecaNaCasa;
    bool condicaoEhUmaDama;

    if (seletorX == 4.5f)
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas_J1);
    }
    else
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (condicaoEhUmaDama &&
        podeMoverParaBaixo(seletorX_aux, seletorY_aux, seletorX, seletorY) &&
        podeMoverParaEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = false;
    }
}

void moverParaDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], int damas[12], bool pecaEstaSelecionada)
{
    bool condicaoTemPecaNaCasa;
    bool condicaoEhUmaDama;

    if (seletorX == 4.5f)
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas_J1);
    }
    else
    {
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (condicaoEhUmaDama &&
        podeMoverParaBaixo(seletorX_aux, seletorY_aux, seletorX, seletorY) &&
        podeMoverParaDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'd'; // DIREITA INFERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = false;
    }
}

bool podeComerParaEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
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
        if ((seletorX - 0.5f - 1.0f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE COMER DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2))
                {
                    return true;
                }
            }
        }
    }
    else if (seletorX == 11.5f) // <
    {
        if ((seletorX - 0.5f + 1.0f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE COMER DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool podeComerParaDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
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
        if ((seletorX - 0.5f + 1.0f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J2))
                {
                    return true;
                }
            }
        }
    }
    else if (seletorX == 11.5f) // >
    {
        if ((seletorX - 0.5f - 1.0f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool podeComerParaEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
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
        if ((seletorX - 0.5f - 1.0f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2))
                {
                    return true;
                }
            }
        }
    }
    else if (seletorX == 11.5f) // <
    {
        if ((seletorX - 0.5f + 1.0f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool podeComerParaDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
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
        if ((seletorX - 0.5f + 1.0f) + seletorX_aux < yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux + 2.0f, seletorY_aux - 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux + 1.0f, seletorY_aux - 1.0f, seletorX, seletorY, pecas_J2))
                {
                    return true;
                }
            }
        }
    }
    else if (seletorX == 11.5f) // >
    {
        if ((seletorX - 0.5f - 1.0f) + seletorX_aux > yA3Casa) // SE FOR UMA CASA DO TABULEIRO.
        {
            if (!temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J1) &&
                !temPecaNaCasa(seletorX_aux - 2.0f, seletorY_aux + 2.0f, seletorX, seletorY, pecas_J2)) // SE NÃO EXISTE OUTRA PECA NA OPÇÃO DE MOVIMENTO DA PECA SELECIONADA.
            {
                if (temPecaNaCasa(seletorX_aux - 1.0f, seletorY_aux + 1.0f, seletorX, seletorY, pecas_J1))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void comerParaEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], bool pecaEstaSelecionada)
{
    float comerY;
    bool condicaoTemPecaNaCasa;

    if (seletorY == 4.5f)
    {
        comerY = 1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
    }
    else
    {
        comerY = -1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (podeMoverParaCima(seletorX_aux, seletorY_aux + comerY, seletorX, seletorY) &&
        podeComerParaEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = true;
    }
}

void comerParaDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                              float pecas_J1[12][3], float pecas_J2[12][3], bool pecaEstaSelecionada)
{
    float comerY;
    bool condicaoTemPecaNaCasa;

    if (seletorY == 4.5f)
    {
        comerY = 1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
    }
    else
    {
        comerY = -1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (podeMoverParaCima(seletorX_aux, seletorY_aux + comerY, seletorX, seletorY) &&
        podeComerParaDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = true;
    }
}

void comerParaEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], int damas[12], bool pecaEstaSelecionada)
{
    float comerY;
    bool condicaoTemPecaNaCasa;
    bool condicaoEhUmaDama;

    if (seletorX == 4.5f)
    {
        comerY = -1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas_J1);
    }
    else
    {
        comerY = 1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (condicaoEhUmaDama &&
        podeMoverParaBaixo(seletorX_aux, seletorY_aux + comerY, seletorX, seletorY) &&
        podeComerParaEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = true;
    }
}

void comerParaDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
                               float pecas_J1[12][3], float pecas_J2[12][3], int damas[12], bool pecaEstaSelecionada)
{
    float comerY;
    bool condicaoTemPecaNaCasa;
    bool condicaoEhUmaDama;

    if (seletorX == 4.5f)
    {
        comerY = -1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas_J1);
    }
    else
    {
        comerY = 1.0f;
        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas_J2);
    }

    // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
    if (condicaoEhUmaDama &&
        podeMoverParaBaixo(seletorX_aux, seletorY_aux + comerY, seletorX, seletorY) &&
        podeComerParaDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
        condicaoTemPecaNaCasa && pecaEstaSelecionada)
    {
        moverPeca_direcao = 'd'; // DIREITA INFERIOR.
        moverPeca_animacao = true;
        vaiComerPeca = true;
    }
}

void opcaoSeletorEsquerdaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY, float comerX, float comerY)
{
    float somaX;
    float somaY;

    int corR;
    int corB;

    if (seletorX == 4.5f) // SE É O JOGADOR 1.
    {
        somaX = 3.5f;
        somaY = 5.5f;
        corR = 0;
        corB = 40;
    }
    else if (seletorX == 11.5f) // SE É O JOGADOR 2.
    {
        somaX = 12.5f;
        somaY = 10.5f;
        corR = 40;
        corB = 0;
    }

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.01f); // PARA FICAR MAIS ALTO QUE AS CASAS DO TABULEIRO.

    if (comerX != 0.0f || comerY != 0.0f) // SE FOR PARA COMER UMA PEÇA.
    {
        glTranslatef(somaX + seletorX_aux + comerX, somaY + seletorY_aux + comerY, 1.625f);
    }
    else
    {
        glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    }

    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorEsquerdaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY, float comerX, float comerY)
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

    if (comerX != 0.0f || comerY != 0.0f) // SE FOR PARA COMER UMA PEÇA.
    {
        glTranslatef(somaX + seletorX_aux + comerX, somaY + seletorY_aux + comerY, 1.625f);
    }
    else
    {
        glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    }

    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaSuperior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY, float comerX, float comerY)
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

    if (comerX != 0.0f || comerY != 0.0f) // SE FOR PARA COMER UMA PEÇA.
    {
        glTranslatef(somaX + seletorX_aux + comerX, somaY + seletorY_aux + comerY, 1.625f);
    }
    else
    {
        glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    }

    glScalef(1.0f, 1.0f, 0.125f);
    cubo(corR, 0, corB, 150, GL_FILL);
    cubo(0, 0, 0, 150, GL_LINE);

    glPopMatrix();
}

void opcaoSeletorDireitaInferior(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY, float comerX, float comerY)
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

    if (comerX != 0.0f || comerY != 0.0f) // SE FOR PARA COMER UMA PEÇA.
    {
        glTranslatef(somaX + seletorX_aux + comerX, somaY + seletorY_aux + comerY, 1.625f);
    }
    else
    {
        glTranslatef(somaX + seletorX_aux, somaY + seletorY_aux, 1.625f);
    }

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

    float comer_aux;

    if (seletorX == 4.5f)
    {
        somaX = 4.5f;
        somaY = 4.5f;
        corR = 0;
        corB = 40;

        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, damas);

        comer_aux = 1.0f;
    }
    else if (seletorX == 11.5f)
    {
        somaX = 11.5f;
        somaY = 11.5f;
        corR = 40;
        corB = 0;

        condicaoTemPecaNaCasa = temPecaNaCasa(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2);
        condicaoEhUmaDama = ehUmaDama(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J2, damas);

        comer_aux = -1.0f;
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
                    opcaoSeletorEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, 0.0f, 0.0f);
                }
                else if (podeComerParaEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
                         podeMoverParaCima(seletorX_aux, seletorY_aux + comer_aux, seletorX, seletorY))
                {
                    opcaoSeletorEsquerdaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, -comer_aux, comer_aux);
                }

                if (podeMoverParaDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                {
                    opcaoSeletorDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, 0.0f, 0.0f);
                }
                else if (podeComerParaDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
                         podeMoverParaCima(seletorX_aux, seletorY_aux + comer_aux, seletorX, seletorY))
                {
                    opcaoSeletorDireitaSuperior(seletorX_aux, seletorY_aux, seletorX, seletorY, comer_aux, comer_aux);
                }
            }

            if (condicaoEhUmaDama) // SE A PEÇA É UMA DAMA.
            {
                if (podeMoverParaBaixo(seletorX_aux, seletorY_aux, seletorX, seletorY))
                {
                    if (podeMoverParaEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                    {
                        opcaoSeletorEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, 0.0f, 0.0f);
                    }
                    else if (podeComerParaEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
                             podeMoverParaBaixo(seletorX_aux, seletorY_aux - comer_aux, seletorX, seletorY))
                    {
                        opcaoSeletorEsquerdaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, -comer_aux, -comer_aux);
                    }

                    if (podeMoverParaDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2))
                    {
                        opcaoSeletorDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, 0.0f, 0.0f);
                    }
                    else if (podeComerParaDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, pecas_J1, pecas_J2) &&
                             podeMoverParaBaixo(seletorX_aux, seletorY_aux - comer_aux, seletorX, seletorY))
                    {
                        opcaoSeletorDireitaInferior(seletorX_aux, seletorY_aux, seletorX, seletorY, comer_aux, -comer_aux);
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
        if (pecas_J1[i][0] != 0 && pecas_J1[i][1] != 0 && pecas_J1[i][2] != 0)
        {
            glPushMatrix();

            glTranslatef(pecas_J1[i][0], pecas_J1[i][1], pecas_J1[i][2]);
            glScalef(0.4f, 0.4f, 0.125f);
            cilindro(100, 100, 255, 255, GL_FILL);

            glPopMatrix();
        }
    }

    // JOGADOR 2
    for (int i = 0; i < 12; i++)
    {
        if (pecas_J2[i][0] != 0 && pecas_J2[i][1] != 0 && pecas_J2[i][2] != 0)
        {
            glPushMatrix();

            glTranslatef(pecas_J2[i][0], pecas_J2[i][1], pecas_J2[i][2]);
            glScalef(0.4f, 0.4f, 0.125f);
            cilindro(255, 100, 100, 255, GL_FILL);

            glPopMatrix();
        }
    }
}

#endif
