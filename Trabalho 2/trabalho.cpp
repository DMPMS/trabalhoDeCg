// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/pecas.h"

#include "stdbool.h"

float eyeX = 0.0f;
float eyeY = -50.0f;
float eyeZ = 70.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA DO JOGADOR 1.
float seletorX_J1 = 4.5f;
float seletorY_J1 = 4.5f;
float seletorX_J1_aux = 0.0f;
float seletorY_J1_aux = 0.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA DO JOGADOR 2.
float seletorX_J2 = 11.5f;
float seletorY_J2 = 11.5f;
float seletorX_J2_aux = 0.0f;
float seletorY_J2_aux = 0.0f;

// PECAS[12][3]

// POSIÇÕES DE CADA PEÇA DO JOGADOR 1.
// float pecas_J1[12][3] = {{5.5f, 6.5f, 1.625f}, {7.5f, 6.5f, 1.625f}, {9.5f, 6.5f, 1.625f}, {11.5f, 6.5f, 1.625f},
//                          {4.5f, 5.5f, 1.625f}, {6.5f, 5.5f, 1.625f}, {8.5f, 5.5f, 1.625f}, {10.5f, 5.5f, 1.625f},
//                          {5.5f, 4.5f, 1.625f}, {7.5f, 4.5f, 1.625f}, {9.5f, 4.5f, 1.625f}, {11.5f, 4.5f, 1.625f}}

float pecas_J1[12][3] = {{5.5f, 6.5f, 1.625f}, {7.5f, 6.5f, 1.625f}, {9.5f, 6.5f, 1.625f}, {11.5f, 6.5f, 1.625f}, {4.5f, 5.5f, 1.625f}, {6.5f, 5.5f, 1.625f}, {8.5f, 5.5f, 1.625f}, {10.5f, 5.5f, 1.625f}, {5.5f, 4.5f, 1.625f}, {7.5f, 4.5f, 1.625f}, {9.5f, 4.5f, 1.625f}, {11.5f, 4.5f, 1.625f}};

// POSIÇÕES DE CADA PEÇA DO JOGADOR 2.
// float pecas_J2[12][3] = {{10.5f, 11.5f, 1.625f}, {8.5f, 11.5f, 1.625f}, {6.5f, 11.5f, 1.625f}, {4.5f, 11.5f, 1.625f},
//                          {11.5f, 10.5f, 1.625f}, {9.5f, 10.5f, 1.625f}, {7.5f, 10.5f, 1.625f}, {5.5f, 10.5f, 1.625f},
//                          {10.5f, 9.5f, 1.625f}, {8.5f, 9.5f, 1.625f}, {6.5f, 9.5f, 1.625f}, {4.5f, 9.5f, 1.625f}};
float pecas_J2[12][3] = {{10.5f, 11.5f, 1.625f}, {8.5f, 11.5f, 1.625f}, {6.5f, 11.5f, 1.625f}, {4.5f, 11.5f, 1.625f}, {11.5f, 10.5f, 1.625f}, {9.5f, 10.5f, 1.625f}, {7.5f, 10.5f, 1.625f}, {5.5f, 10.5f, 1.625f}, {10.5f, 9.5f, 1.625f}, {8.5f, 9.5f, 1.625f}, {6.5f, 9.5f, 1.625f}, {4.5f, 9.5f, 1.625f}};

// PARA INDICAR QUAIS PEÇAS DOS JOGADORES JÁ SE TORNARAM DAMAS.
int damas_J1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int damas_J2[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool pecaEstaSelecionada = true; // PARA AUXILIAR A EXIBIR (OU NÃO) AS OPÇÕES DE MOVIMENTO DA PEÇA.
bool moverPeca_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA PEÇA.
char moverPeca_direcao;          // PARA DEFINIR QUAL DIREÇÃO A PEÇA DEVE IR.

int jogadorDaVez = 1; // JOGADOR 1 = 1. JOGADOR 2 = -1;

float moverCamera_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA CÂMERA.
float moverCamera_aux = 1.0f;       // PARA AUXILIAR NA MOVIMENTAÇÃO DA CÂMERA.

bool vaiComerPeca = false;

void timer(int);

void inicio()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);                                // PARA USAR OPACIDADE.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // PARA USAR OPACIDADE.
}

void tecladoASCII(unsigned char key, int x, int y)
{
    // MOVER CÂMERA.
    switch (key)
    {
    case '7':
        eyeX += 3.0f;
        break;
    case '1':
        eyeX -= 3.0f;
        break;
    case '8':
        eyeY += 3.0f;
        break;
    case '2':
        eyeY -= 3.0f;
        break;
    case '9':
        eyeZ += 3.0f;
        break;
    case '3':
        eyeZ -= 3.0f;
        break;
    }

    switch (key)
    {
    case 'e':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1) &&
                podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaEsquerdaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1) &&
                     podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux - 1.0f, seletorX_J1, seletorY_J1) &&
                     podeComerParaEsquerdaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2) &&
                podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaEsquerdaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2) &&
                     podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux + 1.0f, seletorX_J2, seletorY_J2) &&
                     podeComerParaEsquerdaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        break;
    case 'E':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaEsquerdaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux + 1.0f, seletorX_J1, seletorY_J1) &&
                     podeComerParaEsquerdaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaEsquerdaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux - 1.0f, seletorX_J2, seletorY_J2) &&
                     podeComerParaEsquerdaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        break;
    case 'd':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1) &&
                podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaDireitaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1) &&
                     podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux - 1.0f, seletorX_J1, seletorY_J1) &&
                     podeComerParaDireitaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2) &&
                podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaDireitaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2) &&
                     podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux + 1.0f, seletorX_J2, seletorY_J2) &&
                     podeComerParaDireitaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        break;
    case 'D':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorX_J1_aux, seletorY_J1_aux) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaDireitaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux + 1.0f, seletorX_J1, seletorY_J1) &&
                     podeComerParaDireitaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorX_J2_aux, seletorY_J2_aux) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaDireitaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = false;
            }
            else if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux - 1.0f, seletorX_J2, seletorY_J2) &&
                     podeComerParaDireitaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2) &&
                     temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2) &&
                     pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
                vaiComerPeca = true;
            }
        }
        break;
    }

    glutPostRedisplay();
}

void tecladoSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorX_J1_aux < 11.0f)
            {
                seletorX_J1_aux += 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorX_J2_aux > 4.0f)
            {
                seletorX_J2_aux -= 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_LEFT:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorX_J1_aux > 4.0f)
            {
                seletorX_J1_aux -= 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorX_J2_aux < 11.0f)
            {
                seletorX_J2_aux += 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_UP:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorY_J1_aux < 11.0f)
            {
                seletorY_J1_aux += 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorY_J2_aux > 4.0f)
            {
                seletorY_J2_aux -= 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_DOWN:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorY_J1_aux > 4.0f)
            {
                seletorY_J1_aux -= 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorY_J2_aux < 11.0f)
            {
                seletorY_J2_aux += 1.0f;
                pecaEstaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_F1:
        pecaEstaSelecionada += -1; // HABILITA A EXIBIÇÃO DAS OPÇÕES DE MOVIMENTO DA PEÇA SELECIONADA.
        break;
    }

    glutPostRedisplay();
}

void projecao()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, 500.0f);
}

void camera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eyeX, eyeY, eyeZ,
        8.0f, 8.0f, 0.0f,
        0.0f, 0.0f, 1.0f);
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projecao();
    camera();

    baseDeMadeira();
    tabuleiro();

    pecas();

    if (jogadorDaVez == 1)
    {
        seletorDePeca(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1, pecaEstaSelecionada);
    }
    else
    {
        seletorDePeca(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, damas_J2, pecaEstaSelecionada);
    }

    // eixos();

    glutSwapBuffers();
}

void moverPeca(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
               float pecas[12][3], int damas[12], bool vaiComerPeca)
{
    float pecaDestino_aux;

    if (seletorX == 4.5f)
    {
        pecaDestino_aux = 1.0f; // PARA O JOGADOR 1.

        if (vaiComerPeca)
        {
            pecaDestino_aux += 1.0f;
        }
    }
    else if (seletorX == 11.5f)
    {
        pecaDestino_aux = -1.0f; // PARA O JOGADOR 2.

        if (vaiComerPeca)
        {
            pecaDestino_aux += -1.0f;
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (seletorX + seletorX_aux == pecas[i][0] && seletorY + seletorY_aux == pecas[i][1]) // SE É A PEÇA SELECIONADA.
        {
            float pecasX_destino;
            float pecasY_destino;

            if (moverPeca_direcao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasX_destino = pecas[i][0] - pecaDestino_aux;
                pecasY_destino = pecas[i][1] + pecaDestino_aux;
            }
            else if (moverPeca_direcao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasX_destino = pecas[i][0] - pecaDestino_aux;
                pecasY_destino = pecas[i][1] - pecaDestino_aux;
            }
            else if (moverPeca_direcao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasX_destino = pecas[i][0] + pecaDestino_aux;
                pecasY_destino = pecas[i][1] + pecaDestino_aux;
            }
            else if (moverPeca_direcao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
            {
                pecasX_destino = pecas[i][0] + pecaDestino_aux;
                pecasY_destino = pecas[i][1] - pecaDestino_aux;
            }

            while (pecas[i][2] < 2.0f) // LEVANTAR A PEÇA
            {
                pecas[i][2] += 0.025f;
                desenha();
            }

            if (pecas[i][0] > pecasX_destino && pecas[i][1] < pecasY_destino) // PEÇA IRÁ PARA A ESQUERDA SUPERIOR.
            {
                while (pecas[i][0] > pecasX_destino && pecas[i][1] < pecasY_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecas[i][0] -= 0.01;
                    pecas[i][1] += 0.01;

                    desenha();
                }
            }
            else if (pecas[i][0] > pecasX_destino && pecas[i][1] > pecasY_destino) // PEÇA IRÁ PARA A ESQUERDA INFERIOR.
            {
                while (pecas[i][0] > pecasX_destino && pecas[i][1] > pecasY_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecas[i][0] -= 0.01;
                    pecas[i][1] -= 0.01;

                    desenha();
                }
            }
            else if (pecas[i][0] < pecasX_destino && pecas[i][1] < pecasY_destino) // PEÇA IRÁ PARA DIREITA SUPERIOR.
            {
                while (pecas[i][0] < pecasX_destino && pecas[i][1] < pecasY_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecas[i][0] += 0.01;
                    pecas[i][1] += 0.01;

                    desenha();
                }
            }
            else if (pecas[i][0] < pecasX_destino && pecas[i][1] > pecasY_destino) // PEÇA IRÁ PARA DIREITA INFERIOR.
            {
                while (pecas[i][0] < pecasX_destino && pecas[i][1] > pecasY_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecas[i][0] += 0.01;
                    pecas[i][1] -= 0.01;

                    desenha();
                }
            }

            while (pecas[i][2] > 1.625f) // DESCER A PEÇA.
            {
                pecas[i][2] -= 0.025f;
                desenha();
            }

            moverCamera_animacao = true; // ATIVA A ANIMAÇÃO DE MOVIMENTAÇÃO DE CÂMERA.
            moverPeca_animacao = false;  // DESABILITA A ANIMAÇÃO DE MOVIMENTAÇÃO DA PEÇA.

            if ((seletorY == 4.5f && pecasY_destino == 11.5f) || (seletorY == 11.5f && pecasY_destino == 4.5f)) // SE CHEGOU NO TOPO DO TABULEIRO.
            {
                damas[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecas[i][0] = pecasX_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecas[i][1] = pecasY_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
    }
}

void removerPeca(float pecaX, float pecaY, float pecas[12][3])
{
    for (int i = 0; i < 12; i++)
    {
        if (pecaX == pecas[i][0] && pecaY == pecas[i][1]) // SE É A PEÇA A SER REMOVIDA.
        {
            pecas[i][0] = 0.0f;
            pecas[i][1] = 0.0f;
            pecas[i][2] = 0.0f;
        }
    }
}

void comerPeca(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
               float pecasJogador[12][3], float pecasAdversario[12][3], int damas[12])
{
    moverPeca(seletorX_aux, seletorY_aux, seletorX, seletorY,
              pecasJogador, damas, vaiComerPeca);

    float comerX;
    float comerY;

    if (seletorX == 4.5f)
    {
        comerX = 1.0f;
        comerY = 1.0f;
    }
    else if (seletorX == 11.5f)
    {
        comerX = -1.0f;
        comerY = -1.0f;
    }

    if (moverPeca_direcao == 'e')
    {
        removerPeca(seletorX_aux + seletorX - comerX, seletorY_aux + seletorX - comerY, pecasAdversario);
    }
    else if (moverPeca_direcao == 'E')
    {
        removerPeca(seletorX_aux + seletorX - comerX, seletorY_aux + seletorX + comerY, pecasAdversario);
    }
    else if (moverPeca_direcao == 'd')
    {
        removerPeca(seletorX_aux + seletorX + comerX, seletorY_aux + seletorX - comerY, pecasAdversario);
    }
    else if (moverPeca_direcao == 'D')
    {
        removerPeca(seletorX_aux + seletorX + comerX, seletorY_aux + seletorX + comerY, pecasAdversario);
    }
}

void moverCamera()
{
    if (moverCamera_aux == 1.0f)
    {
        while (eyeY != 66.0f)
        {
            eyeY += moverCamera_aux;
            desenha();
        }
    }
    else
    {
        while (eyeY != -50.0f)
        {
            eyeY += moverCamera_aux;
            desenha();
        }
    }

    moverCamera_aux *= -1.0f;     // PARA ALTERNAR O DESTINO NA PRÓXIMA MOVIMENTAÇÃO DA CÂMERA (AO TROCAR A VEZ DO JOGADOR).
    moverCamera_animacao = false; // PARA FINALIZAR A MOVIMENTAÇÃO DA CÂMERA.

    jogadorDaVez *= -1;          // AO ENCERRAR A MOVIMENTAÇÃO DA CÂMERA, TROCA A VEZ DO JOGADOR.
    pecaEstaSelecionada = false; // DESABILITA AS OPÇÕES DE MOVIMENTO DO SELETOR DE PEÇAS.
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(110, 50);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Forza Horizon 6");

    glutTimerFunc(1000 / 144, timer, 0);

    inicio();

    glutDisplayFunc(desenha);

    glutKeyboardFunc(tecladoASCII);
    glutSpecialFunc(tecladoSpecial);

    glutMainLoop();

    return 0;
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 144, timer, 0);

    if (moverPeca_animacao)
    {
        if (jogadorDaVez == 1)
        {
            if (vaiComerPeca)
            {
                comerPeca(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1);
            }
            else
            {
                moverPeca(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1, vaiComerPeca);
            }
        }
        else
        {
            if (vaiComerPeca)
            {
                comerPeca(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, pecas_J1, damas_J2);
            }
            else
            {
                moverPeca(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2, vaiComerPeca);
            }
        }
    }

    if (moverCamera_animacao)
    {
        moverCamera(); // TROCAR A VISÃO DO TABULEIRO DE DAMAS AO TROCAR A VEZ DO JOGADOR.
    }
}
