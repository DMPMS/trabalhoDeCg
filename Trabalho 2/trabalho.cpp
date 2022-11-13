// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/pecas.h"

#include "stdbool.h"
#include "texturas/textura.h"

float eyeX = 8.0f;
float eyeY = -50.0f;
float eyeZ = 70.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA DO JOGADOR 1.
float seletorX_J1 = 4.5f;     // POSIÇÃO X DO SELETOR AO INICIAR A APLICAÇÃO.
float seletorY_J1 = 4.5f;     // POSIÇÃO Y DO SELETOR AO INICIAR A APLICAÇÃO.
float seletorX_J1_aux = 0.0f; // IRÁ VARIAR PARA SER SOMADA AO seletorX_J1 PARA MOVER O SELETOR.
float seletorY_J1_aux = 0.0f; // IRÁ VARIAR PARA SER SOMADA AO seletorY_J1 PARA MOVER O SELETOR.

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA DO JOGADOR 2.
float seletorX_J2 = 11.5f;    // POSIÇÃO X DO SELETOR AO INICIAR A APLICAÇÃO.
float seletorY_J2 = 11.5f;    // POSIÇÃO Y DO SELETOR AO INICIAR A APLICAÇÃO.
float seletorX_J2_aux = 0.0f; // IRÁ VARIAR PARA SER SOMADA AO seletorX_J2 PARA MOVER O SELETOR.
float seletorY_J2_aux = 0.0f; // IRÁ VARIAR PARA SER SOMADA AO seletorY_J2 PARA MOVER O SELETOR.

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
int damas_J1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // SE O INDICE FOR IGUAL A 1, A PEÇA NESSA POSICÃO SERÁ UMA DAMA.
int damas_J2[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // SE O INDICE FOR IGUAL A 1, A PEÇA NESSA POSICÃO SERÁ UMA DAMA.

bool pecaEstaSelecionada = true; // PARA AUXILIAR A EXIBIR (OU NÃO) AS OPÇÕES DE MOVIMENTO DA PEÇA.
bool moverPecaTabuleiro_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA PEÇA.
char moverPecaTabuleiro_direcao;          // PARA DEFINIR QUAL DIREÇÃO A PEÇA DEVE IR.

int jogadorDaVez = 1; // JOGADOR 1 = 1. JOGADOR 2 = -1;

float moverCamera_animacao = false; // PARA INICIAR E FINALIZAR ANIMAÇÃO DE MOVIMENTAÇÃO DA CÂMERA.
float moverCamera_aux = 1.0f;       // PARA AUXILIAR NA MOVIMENTAÇÃO DA CÂMERA.

bool vaiComerPeca = false; // PARA DEFINIR SE A AÇÃO DE MOVIMENTO DA PEÇA SERÁ PARA COMER UMA PEÇA ADVERSÁRIA.

// PARA INDICAR AONDE A PEÇA VAI FICAR APÓS SER COMIDA.
float cemiterioX_J1 = 2.5f;
float cemiterioY_J1 = 1.5f;
float cemiterioX_J2 = 13.5f;
float cemiterioY_J2 = 14.5f;

int FPS = 144;

int texID[2];
Textura tex;

void timer(int);

void inicio()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);                                // PARA USAR OPACIDADE.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // PARA USAR OPACIDADE.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    //textura 1
    tex.carregar("images/madeira01.jpeg");
    texID[0] = tex.get_id();
    //textura 2
    tex.carregar("images/madeira02.jpeg");
    texID[1] = tex.get_id();
    cout << texID[0] << endl;
    cout << texID[1] << endl;

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
            moverParaEsquerdaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1, pecaEstaSelecionada);
            comerParaEsquerdaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1, pecaEstaSelecionada);
        }
        else
        {
            moverParaEsquerdaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, damas_J2, pecaEstaSelecionada);
            comerParaEsquerdaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, damas_J2, pecaEstaSelecionada);
        }
        break;
    case 'E':
        if (jogadorDaVez == 1)
        {
            moverParaEsquerdaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, pecaEstaSelecionada);
            comerParaEsquerdaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, pecaEstaSelecionada);
        }
        else
        {
            moverParaEsquerdaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, pecaEstaSelecionada);
            comerParaEsquerdaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, pecaEstaSelecionada);
        }
        break;
    case 'd':
        if (jogadorDaVez == 1)
        {
            moverParaDireitaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1, pecaEstaSelecionada);
            comerParaDireitaInferior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1, pecaEstaSelecionada);
        }
        else
        {
            moverParaDireitaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, damas_J2, pecaEstaSelecionada);
            comerParaDireitaInferior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, damas_J2, pecaEstaSelecionada);
        }
        break;
    case 'D':
        if (jogadorDaVez == 1)
        {
            moverParaDireitaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, pecaEstaSelecionada);
            comerParaDireitaSuperior(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, pecaEstaSelecionada);
        }
        else
        {
            moverParaDireitaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, pecaEstaSelecionada);
            comerParaDireitaSuperior(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J1, pecas_J2, pecaEstaSelecionada);
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

    baseDeMadeira(texID);
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

void moverPecaTabuleiro(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
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

            if (moverPecaTabuleiro_direcao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasX_destino = pecas[i][0] - pecaDestino_aux;
                pecasY_destino = pecas[i][1] + pecaDestino_aux;
            }
            else if (moverPecaTabuleiro_direcao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasX_destino = pecas[i][0] - pecaDestino_aux;
                pecasY_destino = pecas[i][1] - pecaDestino_aux;
            }
            else if (moverPecaTabuleiro_direcao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasX_destino = pecas[i][0] + pecaDestino_aux;
                pecasY_destino = pecas[i][1] + pecaDestino_aux;
            }
            else if (moverPecaTabuleiro_direcao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
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
            moverPecaTabuleiro_animacao = false;  // DESABILITA A ANIMAÇÃO DE MOVIMENTAÇÃO DA PEÇA.

            if ((seletorY == 4.5f && pecasY_destino == 11.5f) || (seletorY == 11.5f && pecasY_destino == 4.5f)) // SE CHEGOU NO TOPO DO TABULEIRO.
            {
                damas[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecas[i][0] = pecasX_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecas[i][1] = pecasY_destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
    }
}

void moverPecaCemiterio(float pecaX, float pecaY, float pecas[12][3])
{
    float cemiterioX;
    float cemiterioY;

    if (pecas == pecas_J1) // SE A PEÇA A SER REMOVIDA É DO JOGADOR 1.
    {
        cemiterioX = cemiterioX_J1;
        cemiterioY = cemiterioY_J1;
    }
    else if (pecas == pecas_J2) // SE A PEÇA A SER REMOVIDA É DO JOGADOR 2.
    {
        cemiterioX = cemiterioX_J2;
        cemiterioY = cemiterioY_J2;
    }

    for (int i = 0; i < 12; i++)
    {
        if (pecaX == pecas[i][0] && pecaY == pecas[i][1]) // SE É A PEÇA A SER REMOVIDA.
        {

            while (pecas[i][2] < 2.0f) // LEVANTAR A PEÇA.
            {
                pecas[i][2] += 0.025f;
                desenha();
            }

            if (pecas[i][0] > cemiterioX) // SE O x DO VÉRTICE A3 DA PEÇA A SER REMOVIDA FOR MAIOR QUE O x DA POSIÇÃO QUE ELA DEVE FICAR NO CEMITÉRIO.
            {
                while (pecas[i][0] > cemiterioX) // MOVER ATÉ O x DA POSIÇÃO NO CEMITÉRIO.
                {
                    pecas[i][0] -= 0.01;
                    desenha();
                }
            }
            else if (pecas[i][0] < cemiterioX) // SE O x DO VÉRTICE A3 DA DAMA A SER REMOVIDA FOR MENOR QUE O x DA POSIÇÃO QUE ELA DEVE FICAR NO CEMITÉRIO.
            {
                while (pecas[i][0] < cemiterioX) // MOVER ATÉ O x DA POSIÇÃO NO CEMITÉRIO.
                {
                    pecas[i][0] += 0.01;
                    desenha();
                }
            }

            if (cemiterioY == cemiterioY_J1) // SE A PEÇA A SER REMOVIDA É DO JOGADOR 1.
            {
                while (pecas[i][1] > cemiterioY) // MOVER ATÉ O y DA POSIÇÃO NO CEMITÉRIO.
                {
                    pecas[i][1] -= 0.01;
                    desenha();
                }

                cemiterioX_J1 += 1.0f; // DEFININDO A LOCALIZAÇÃO DA PRÓXIMA POSIÇÃO DO CEMITÉRIO DO JOGADOR 1.
            }
            else if (cemiterioY == cemiterioY_J2) // SE A PEÇA A SER REMOVIDA É DO JOGADOR 2.
            {
                while (pecas[i][1] < cemiterioY) // MOVER ATÉ O y DA POSIÇÃO NO CEMITÉRIO.
                {
                    pecas[i][1] += 0.01;
                    desenha();
                }

                cemiterioX_J2 -= 1.0f; // DEFININDO A LOCALIZAÇÃO DA PRÓXIMA 'COVA' DO CEMITÉRIO DO JOGADOR 2.
            }

            while (pecas[i][2] > 1.0f) // DESCER A PEÇA.
            {
                pecas[i][2] -= 0.025f;
                desenha();
            }
        }
    }
}

void comerPeca(float seletorX_aux, float seletorY_aux, float seletorX, float seletorY,
               float pecasJogador[12][3], float pecasAdversario[12][3], int damas[12])
{
    moverPecaTabuleiro(seletorX_aux, seletorY_aux, seletorX, seletorY,
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

    if (moverPecaTabuleiro_direcao == 'e')
    {
        moverPecaCemiterio(seletorX_aux + seletorX - comerX, seletorY_aux + seletorX - comerY, pecasAdversario);
    }
    else if (moverPecaTabuleiro_direcao == 'E')
    {
        moverPecaCemiterio(seletorX_aux + seletorX - comerX, seletorY_aux + seletorX + comerY, pecasAdversario);
    }
    else if (moverPecaTabuleiro_direcao == 'd')
    {
        moverPecaCemiterio(seletorX_aux + seletorX + comerX, seletorY_aux + seletorX - comerY, pecasAdversario);
    }
    else if (moverPecaTabuleiro_direcao == 'D')
    {
        moverPecaCemiterio(seletorX_aux + seletorX + comerX, seletorY_aux + seletorX + comerY, pecasAdversario);
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

    glutTimerFunc(1000 / FPS, timer, 0);

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
    glutTimerFunc(1000 / FPS, timer, 0);

    if (moverPecaTabuleiro_animacao)
    {
        if (jogadorDaVez == 1)
        {
            if (vaiComerPeca)
            {
                comerPeca(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, pecas_J2, damas_J1);
            }
            else
            {
                moverPecaTabuleiro(seletorX_J1_aux, seletorY_J1_aux, seletorX_J1, seletorY_J1, pecas_J1, damas_J1, vaiComerPeca);
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
                moverPecaTabuleiro(seletorX_J2_aux, seletorY_J2_aux, seletorX_J2, seletorY_J2, pecas_J2, damas_J2, vaiComerPeca);
            }
        }
    }

    if (moverCamera_animacao)
    {
        moverCamera(); // TROCAR A VISÃO DO TABULEIRO DE DAMAS AO TROCAR A VEZ DO JOGADOR.
    }
}
