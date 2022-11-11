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

// POSIÇÕES DE CADA PEÇA DO JOGADOR 1.
float pecasX_J1[12] = {5.5f, 7.5f, 9.5f, 11.5f,
                       4.5f, 6.5f, 8.5f, 10.5f,
                       5.5f, 7.5f, 9.5f, 11.5f};
float pecasY_J1[12] = {6.5f, 6.5f, 6.5f, 6.5f,
                       5.5f, 5.5f, 5.5f, 5.5f,
                       4.5f, 4.5f, 4.5f, 4.5f};
float pecasZ_J1[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                       1.625f, 1.625f, 1.625f, 1.625f,
                       1.625f, 1.625f, 1.625f, 1.625f};

// POSIÇÕES DE CADA PEÇA DO JOGADOR 2.
float pecasX_J2[12] = {10.5f, 8.5f, 6.5f, 4.5f,
                       11.5f, 9.5f, 7.5f, 5.5f,
                       10.5f, 8.5f, 6.5f, 4.5f};
float pecasY_J2[12] = {11.5f, 11.5f, 11.5f, 11.5f,
                       10.5f, 10.5f, 10.5f, 10.5f,
                       9.5f, 9.5f, 9.5f, 9.5f};
float pecasZ_J2[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                       1.625f, 1.625f, 1.625f, 1.625f,
                       1.625f, 1.625f, 1.625f, 1.625f};

// PARA INDICAR QUAIS PEÇAS DOS JOGADORES JÁ SE TORNARAM DAMAS.
int damas_J1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int damas_J2[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool pecaEstaSelecionada = true; // PARA AUXILIAR A EXIBIR (OU NÃO) AS OPÇÕES DE MOVIMENTO DA PEÇA.
bool moverPeca_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA PEÇA.
char moverPeca_direcao;          // PARA DEFINIR QUAL DIREÇÃO A PEÇA DEVE IR.

int jogadorDaVez = 1; // JOGADOR 1 = 1. JOGADOR 2 = -1;

float moverCamera_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA CÂMERA.
float moverCamera_aux = 1.0f;       // PARA AUXILIAR NA MOVIMENTAÇÃO DA CÂMERA.

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
            if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, damas_J1) &&
                podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaEsquerdaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2, damas_J2) &&
                podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaEsquerdaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'e'; // ESQUERDA INFERIOR.
                moverPeca_animacao = true;
            }
        }
        break;
    case 'E':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaEsquerdaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaEsquerdaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'E'; // ESQUERDA SUPERIOR.
                moverPeca_animacao = true;
            }
        }
        break;
    case 'd':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, damas_J1) &&
                podeMoverParaBaixo(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaDireitaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
            }
        }
        else
        {
            // temPecaNaCasa() RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDama(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2, damas_J2) &&
                podeMoverParaBaixo(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaDireitaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'd'; // DIREITA INFERIOR.
                moverPeca_animacao = true;
            }
        }
        break;
    case 'D':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorX_J1_aux, seletorY_J1_aux) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1) &&
                podeMoverParaDireitaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorX_J2_aux, seletorY_J2_aux) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeMoverParaCima(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2) &&
                podeMoverParaDireitaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2) &&
                temPecaNaCasa(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J2, pecasY_J2) &&
                pecaEstaSelecionada)
            {
                moverPeca_direcao = 'D'; // DIREITA SUPERIOR.
                moverPeca_animacao = true;
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
        seletorDePeca(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2, damas_J1, pecaEstaSelecionada);
    }
    else
    {
        seletorDePeca(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecasX_J1, pecasY_J1, pecasX_J2, pecasY_J2, damas_J2, pecaEstaSelecionada);
    }

    // eixos();

    glutSwapBuffers();
}

void moverPecaJ1()
{
    // PARA SELECIONAR A PEÇA QUE ESTÁ NA MESMA CASA DO SELETOR DE PEÇAS.
    for (int i = 0; i < 12; i++)
    {
        if (4.5f + seletorX_J1_aux == pecasX_J1[i] && 4.5f + seletorY_J1_aux == pecasY_J1[i])
        {
            float pecasY_J1_destino;
            float pecasX_J1_destino;

            if (moverPeca_direcao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasX_J1_destino = pecasX_J1[i] - 1.0f;
                pecasY_J1_destino = pecasY_J1[i] + 1.0f;
            }
            else if (moverPeca_direcao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasX_J1_destino = pecasX_J1[i] - 1.0f;
                pecasY_J1_destino = pecasY_J1[i] - 1.0f;
            }
            else if (moverPeca_direcao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasX_J1_destino = pecasX_J1[i] + 1.0f;
                pecasY_J1_destino = pecasY_J1[i] + 1.0f;
            }
            else if (moverPeca_direcao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
            {
                pecasX_J1_destino = pecasX_J1[i] + 1.0f;
                pecasY_J1_destino = pecasY_J1[i] - 1.0f;
            }

            while (pecasZ_J1[i] < 2.0f) // LEVANTAR A PEÇA
            {
                pecasZ_J1[i] += 0.025f;
                desenha();
            }

            if (pecasX_J1[i] > pecasX_J1_destino && pecasY_J1[i] < pecasY_J1_destino) // PEÇA IRÁ PARA A ESQUERDA SUPERIOR.
            {
                while (pecasX_J1[i] > pecasX_J1_destino && pecasY_J1[i] < pecasY_J1_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J1[i] -= 0.01;
                    pecasY_J1[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasX_J1[i] > pecasX_J1_destino && pecasY_J1[i] > pecasY_J1_destino) // PEÇA IRÁ PARA A ESQUERDA INFERIOR.
            {
                while (pecasX_J1[i] > pecasX_J1_destino && pecasY_J1[i] > pecasY_J1_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J1[i] -= 0.01;
                    pecasY_J1[i] -= 0.01;

                    desenha();
                }
            }
            else if (pecasX_J1[i] < pecasX_J1_destino && pecasY_J1[i] < pecasY_J1_destino) // PEÇA IRÁ PARA DIREITA SUPERIOR.
            {
                while (pecasX_J1[i] < pecasX_J1_destino && pecasY_J1[i] < pecasY_J1_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J1[i] += 0.01;
                    pecasY_J1[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasX_J1[i] < pecasX_J1_destino && pecasY_J1[i] > pecasY_J1_destino) // PEÇA IRÁ PARA DIREITA INFERIOR.
            {
                while (pecasX_J1[i] < pecasX_J1_destino && pecasY_J1[i] > pecasY_J1_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J1[i] += 0.01;
                    pecasY_J1[i] -= 0.01;

                    desenha();
                }
            }

            while (pecasZ_J1[i] > 1.625f) // DESCER A PEÇA.
            {
                pecasZ_J1[i] -= 0.025f;
                desenha();
            }

            moverCamera_animacao = true;
            moverPeca_animacao = false;

            if (pecasY_J1_destino == 11.5f) // 11.5f É A ÚLTIMA CASA DO TABULEIRO DE DAMA PARA O JOGADOR 1.
            {
                damas_J1[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecasX_J1[i] = pecasX_J1_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecasY_J1[i] = pecasY_J1_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
    }
}

void moverPecaJ2()
{
    // PARA SELECIONAR A PEÇA QUE ESTÁ NA MESMA CASA DO SELETOR DE PEÇAS.
    for (int i = 0; i < 12; i++)
    {
        if (11.5f + seletorX_J2_aux == pecasX_J2[i] && 11.5f + seletorY_J2_aux == pecasY_J2[i])
        {
            float pecasY_J2_destino;
            float pecasX_J2_destino;

            if (moverPeca_direcao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasX_J2_destino = pecasX_J2[i] + 1.0f;
                pecasY_J2_destino = pecasY_J2[i] - 1.0f;
            }
            else if (moverPeca_direcao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasX_J2_destino = pecasX_J2[i] + 1.0f;
                pecasY_J2_destino = pecasY_J2[i] + 1.0f;
            }
            else if (moverPeca_direcao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasX_J2_destino = pecasX_J2[i] - 1.0f;
                pecasY_J2_destino = pecasY_J2[i] - 1.0f;
            }
            else if (moverPeca_direcao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
            {
                pecasX_J2_destino = pecasX_J2[i] - 1.0f;
                pecasY_J2_destino = pecasY_J2[i] + 1.0f;
            }

            while (pecasZ_J2[i] < 2.0f) // LEVANTAR A PEÇA
            {
                pecasZ_J2[i] += 0.025f;
                desenha();
            }

            if (pecasX_J2[i] > pecasX_J2_destino && pecasY_J2[i] < pecasY_J2_destino) // PEÇA IRÁ PARA A ESQUERDA SUPERIOR.
            {
                while (pecasX_J2[i] > pecasX_J2_destino && pecasY_J2[i] < pecasY_J2_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J2[i] -= 0.01;
                    pecasY_J2[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasX_J2[i] > pecasX_J2_destino && pecasY_J2[i] > pecasY_J2_destino) // PEÇA IRÁ PARA A ESQUERDA INFERIOR.
            {
                while (pecasX_J2[i] > pecasX_J2_destino && pecasY_J2[i] > pecasY_J2_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J2[i] -= 0.01;
                    pecasY_J2[i] -= 0.01;

                    desenha();
                }
            }
            else if (pecasX_J2[i] < pecasX_J2_destino && pecasY_J2[i] < pecasY_J2_destino) // PEÇA IRÁ PARA DIREITA SUPERIOR.
            {
                while (pecasX_J2[i] < pecasX_J2_destino && pecasY_J2[i] < pecasY_J2_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J2[i] += 0.01;
                    pecasY_J2[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasX_J2[i] < pecasX_J2_destino && pecasY_J2[i] > pecasY_J2_destino) // PEÇA IRÁ PARA DIREITA INFERIOR.
            {
                while (pecasX_J2[i] < pecasX_J2_destino && pecasY_J2[i] > pecasY_J2_destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasX_J2[i] += 0.01;
                    pecasY_J2[i] -= 0.01;

                    desenha();
                }
            }

            while (pecasZ_J2[i] > 1.625f) // DESCER A PEÇA.
            {
                pecasZ_J2[i] -= 0.025f;
                desenha();
            }

            moverCamera_animacao = true;
            moverPeca_animacao = false;

            if (pecasY_J2_destino == 4.5f) // 4.5f É A ÚLTIMA CASA DO TABULEIRO DE DAMA PARA O JOGADOR 2.
            {
                damas_J2[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecasX_J2[i] = pecasX_J2_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecasY_J2[i] = pecasY_J2_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
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

    moverCamera_aux *= -1.0f;
    moverCamera_animacao = false;

    jogadorDaVez *= -1;
    pecaEstaSelecionada = false;
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
            moverPecaJ1();
        }
        else
        {
            moverPecaJ2();
        }
    }

    if (moverCamera_animacao)
    {
        moverCamera();
    }
}
