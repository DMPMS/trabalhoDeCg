// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/pecasJ1.h"
#include "cenario/pecasJ2.h"

#include "stdbool.h"

float eyeX = 0.0f;
float eyeY = -50.0f;
float eyeZ = 70.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA.
float seletorJ1X = 0.0f;
float seletorJ1Y = 0.0f;

float seletorJ2X = 0.0f;
float seletorJ2Y = 0.0f;

float pecasJ1X[12] = {5.5f, 7.5f, 9.5f, 11.5f,
                      4.5f, 6.5f, 8.5f, 10.5f,
                      5.5f, 7.5f, 9.5f, 11.5f};
float pecasJ1Y[12] = {6.5f, 6.5f, 6.5f, 6.5f,
                      5.5f, 5.5f, 5.5f, 5.5f,
                      4.5f, 4.5f, 4.5f, 4.5f};
float pecasJ1Z[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f};

float pecasJ2X[12] = {10.5f, 8.5f, 6.5f, 4.5f,
                      11.5f, 9.5f, 7.5f, 5.5f,
                      10.5f, 8.5f, 6.5f, 4.5f};
float pecasJ2Y[12] = {11.5f, 11.5f, 11.5f, 11.5f,
                      10.5f, 10.5f, 10.5f, 10.5f,
                      9.5f, 9.5f, 9.5f, 9.5f};
float pecasJ2Z[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f};

int damasJ1[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int damasJ2[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool pecaSelecionada = true;    // PARA EXIBIR (OU NÃO) AS OPÇÕES DE MOVIMENTO DA PEÇA.
bool moverPecaAnimacao = false; // PARA INDICAR SE A ANIMAÇÃO DO MOVIMENTO DA PEÇA FOI FINALIZADA.
char moverPecaDirecao;          // PARA DEFINIR SE A PEÇA VAI PARA ESQUERDA OU DIREITA, SUPERIOR OU INFERIOR.

int jogadorDaVez = 1; // JOGADOR 1 = 1. JOGADOR 2 = -1;

float moverCameraAnimacao = false;
float moverCameraAux = 1.0f;

void timer(int);

void inicio()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);                                // PARA USAR OPACIDADE
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // PARA USAR OPACIDADE
}

void tecladoASCII(unsigned char key, int x, int y)
{
    // MOVER CÂMERA.
    switch (key)
    {
    case '7':
        eyeX += 1.0f;
        break;
    case '1':
        eyeX -= 1.0f;
        break;
    case '8':
        eyeY += 1.0f;
        break;
    case '2':
        eyeY -= 1.0f;
        break;
    case '9':
        eyeZ += 1.0f;
        break;
    case '3':
        eyeZ -= 1.0f;
        break;
    }

    // ESCOLHER PARA ONDE A PEÇA VAI.
    switch (key)
    {
    case 'e':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDamaJ1(seletorJ1X, seletorJ1Y) && podeIrPraBaixoJ1(seletorJ1X, seletorJ1Y) && podeIrPraEsquerdaInferiorJ1(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasaJ1(seletorJ1X, seletorJ1Y))
            {
                moverPecaDirecao = 'e';
                moverPecaAnimacao = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorJ2X, seletorJ2Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeIrPraBaixoJ2(seletorJ2X, seletorJ2Y) && podeIrPraEsquerdaInferiorJ2(seletorJ2X, seletorJ2Y) && pecaSelecionada && temPecaNaCasaJ2(seletorJ2X, seletorJ2Y))
            {
                moverPecaDirecao = 'e';
                moverPecaAnimacao = true;
            }
        }
        break;
    case 'E':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeIrPraCimaJ1(seletorJ1X, seletorJ1Y) && podeIrPraEsquerdaSuperiorJ1(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasaJ1(seletorJ1X, seletorJ1Y))
            {
                moverPecaDirecao = 'E';
                moverPecaAnimacao = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorJ2X, seletorJ2Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeIrPraCimaJ2(seletorJ2X, seletorJ2Y) && podeIrPraEsquerdaSuperiorJ2(seletorJ2X, seletorJ2Y) && pecaSelecionada && temPecaNaCasaJ2(seletorJ2X, seletorJ2Y))
            {
                moverPecaDirecao = 'E';
                moverPecaAnimacao = true;
            }
        }
        break;
    case 'd':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDamaJ1(seletorJ1X, seletorJ1Y) && podeIrPraBaixoJ1(seletorJ1X, seletorJ1Y) && podeIrPraDireitaInferiorJ1(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasaJ1(seletorJ1X, seletorJ1Y))
            {
                moverPecaDirecao = 'd';
                moverPecaAnimacao = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorJ2X, seletorJ2Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (ehUmaDamaJ2(seletorJ2X, seletorJ2Y) && podeIrPraBaixoJ2(seletorJ2X, seletorJ2Y) && podeIrPraDireitaInferiorJ2(seletorJ2X, seletorJ2Y) && pecaSelecionada && temPecaNaCasaJ2(seletorJ2X, seletorJ2Y))
            {
                moverPecaDirecao = 'd';
                moverPecaAnimacao = true;
            }
        }
        break;
    case 'D':
        if (jogadorDaVez == 1)
        {
            // temPecaNaCasaJ1(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeIrPraCimaJ1(seletorJ1X, seletorJ1Y) && podeIrPraDireitaSuperiorJ1(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasaJ1(seletorJ1X, seletorJ1Y))
            {
                moverPecaDirecao = 'D';
                moverPecaAnimacao = true;
            }
        }
        else
        {
            // temPecaNaCasaJ2(seletorJ2X, seletorJ2Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
            if (podeIrPraCimaJ2(seletorJ2X, seletorJ2Y) && podeIrPraDireitaSuperiorJ2(seletorJ2X, seletorJ2Y) && pecaSelecionada && temPecaNaCasaJ2(seletorJ2X, seletorJ2Y))
            {
                moverPecaDirecao = 'D';
                moverPecaAnimacao = true;
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
            if (4.0f + seletorJ1X < 11.0f)
            {
                seletorJ1X += 1.0f;
                pecaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorJ2X > 4.0f)
            {
                seletorJ2X -= 1.0f;
                pecaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_LEFT:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorJ1X > 4.0f)
            {
                seletorJ1X -= 1.0f;
                pecaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorJ2X < 11.0f)
            {
                seletorJ2X += 1.0f;
                pecaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_UP:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorJ1Y < 11.0f)
            {
                seletorJ1Y += 1.0f;
                pecaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorJ2Y > 4.0f)
            {
                seletorJ2Y -= 1.0f;
                pecaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_DOWN:
        if (jogadorDaVez == 1)
        {
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (4.0f + seletorJ1Y > 4.0f)
            {
                seletorJ1Y -= 1.0f;
                pecaSelecionada = false;
            }
        }
        else
        {
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
            // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
            if (11.0f + seletorJ2Y < 11.0f)
            {
                seletorJ2Y += 1.0f;
                pecaSelecionada = false;
            }
        }
        break;
    case GLUT_KEY_F1:
        pecaSelecionada += -1; // HABILITA A EXIBIÇÃO DAS OPÇÕES DE MOVIMENTO DA PEÇA SELECIONADA.
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

    pecasJ1();
    pecasJ2();

    if (jogadorDaVez == 1)
    {
        seletorDePecaJ1(seletorJ1X, seletorJ1Y, pecaSelecionada);
    }
    else
    {
        seletorDePecaJ2(seletorJ2X, seletorJ2Y, pecaSelecionada);
    }

    // eixos();

    glutSwapBuffers();
}

void moverPecaJ1()
{
    // PARA SELECIONAR A PEÇA QUE ESTÁ NA MESMA CASA DO SELETOR DE PEÇAS.
    for (int i = 0; i < 12; i++)
    {
        if (4.5f + seletorJ1X == pecasJ1X[i] && 4.5f + seletorJ1Y == pecasJ1Y[i])
        {
            float pecasJ1Y_Destino;
            float pecasJ1X_Destino;

            if (moverPecaDirecao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] - 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] + 1.0f;
            }
            else if (moverPecaDirecao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] - 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] - 1.0f;
            }
            else if (moverPecaDirecao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] + 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] + 1.0f;
            }
            else if (moverPecaDirecao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] + 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] - 1.0f;
            }

            while (pecasJ1Z[i] < 2.0f) // LEVANTAR A PEÇA
            {
                pecasJ1Z[i] += 0.025f;
                desenha();
            }

            if (pecasJ1X[i] > pecasJ1X_Destino && pecasJ1Y[i] < pecasJ1Y_Destino) // PEÇA IRÁ PARA A ESQUERDA SUPERIOR.
            {
                while (pecasJ1X[i] > pecasJ1X_Destino && pecasJ1Y[i] < pecasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ1X[i] -= 0.01;
                    pecasJ1Y[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasJ1X[i] > pecasJ1X_Destino && pecasJ1Y[i] > pecasJ1Y_Destino) // PEÇA IRÁ PARA A ESQUERDA INFERIOR.
            {
                while (pecasJ1X[i] > pecasJ1X_Destino && pecasJ1Y[i] > pecasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ1X[i] -= 0.01;
                    pecasJ1Y[i] -= 0.01;

                    desenha();
                }
            }
            else if (pecasJ1X[i] < pecasJ1X_Destino && pecasJ1Y[i] < pecasJ1Y_Destino) // PEÇA IRÁ PARA DIREITA SUPERIOR.
            {
                while (pecasJ1X[i] < pecasJ1X_Destino && pecasJ1Y[i] < pecasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ1X[i] += 0.01;
                    pecasJ1Y[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasJ1X[i] < pecasJ1X_Destino && pecasJ1Y[i] > pecasJ1Y_Destino) // PEÇA IRÁ PARA DIREITA INFERIOR.
            {
                while (pecasJ1X[i] < pecasJ1X_Destino && pecasJ1Y[i] > pecasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ1X[i] += 0.01;
                    pecasJ1Y[i] -= 0.01;

                    desenha();
                }
            }

            while (pecasJ1Z[i] > 1.625f) // DESCER A PEÇA.
            {
                pecasJ1Z[i] -= 0.025f;
                desenha();
            }

            moverCameraAnimacao = true;
            moverPecaAnimacao = false;

            if (pecasJ1Y_Destino == 11.5f) // 11.5f É A ÚLTIMA CASA DO TABULEIRO DE DAMA PARA O JOGADOR 1.
            {
                damasJ1[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecasJ1X[i] = pecasJ1X_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecasJ1Y[i] = pecasJ1Y_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
    }
}

void moverPecaJ2()
{
    // PARA SELECIONAR A PEÇA QUE ESTÁ NA MESMA CASA DO SELETOR DE PEÇAS.
    for (int i = 0; i < 12; i++)
    {
        if (11.5f + seletorJ2X == pecasJ2X[i] && 11.5f + seletorJ2Y == pecasJ2Y[i])
        {
            float pecasJ2Y_Destino;
            float pecasJ2X_Destino;

            if (moverPecaDirecao == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasJ2X_Destino = pecasJ2X[i] + 1.0f;
                pecasJ2Y_Destino = pecasJ2Y[i] - 1.0f;
            }
            else if (moverPecaDirecao == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasJ2X_Destino = pecasJ2X[i] + 1.0f;
                pecasJ2Y_Destino = pecasJ2Y[i] + 1.0f;
            }
            else if (moverPecaDirecao == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasJ2X_Destino = pecasJ2X[i] - 1.0f;
                pecasJ2Y_Destino = pecasJ2Y[i] - 1.0f;
            }
            else if (moverPecaDirecao == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
            {
                pecasJ2X_Destino = pecasJ2X[i] - 1.0f;
                pecasJ2Y_Destino = pecasJ2Y[i] + 1.0f;
            }

            while (pecasJ2Z[i] < 2.0f) // LEVANTAR A PEÇA
            {
                pecasJ2Z[i] += 0.025f;
                desenha();
            }

            if (pecasJ2X[i] > pecasJ2X_Destino && pecasJ2Y[i] < pecasJ2Y_Destino) // PEÇA IRÁ PARA A ESQUERDA SUPERIOR.
            {
                while (pecasJ2X[i] > pecasJ2X_Destino && pecasJ2Y[i] < pecasJ2Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ2X[i] -= 0.01;
                    pecasJ2Y[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasJ2X[i] > pecasJ2X_Destino && pecasJ2Y[i] > pecasJ2Y_Destino) // PEÇA IRÁ PARA A ESQUERDA INFERIOR.
            {
                while (pecasJ2X[i] > pecasJ2X_Destino && pecasJ2Y[i] > pecasJ2Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ2X[i] -= 0.01;
                    pecasJ2Y[i] -= 0.01;

                    desenha();
                }
            }
            else if (pecasJ2X[i] < pecasJ2X_Destino && pecasJ2Y[i] < pecasJ2Y_Destino) // PEÇA IRÁ PARA DIREITA SUPERIOR.
            {
                while (pecasJ2X[i] < pecasJ2X_Destino && pecasJ2Y[i] < pecasJ2Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ2X[i] += 0.01;
                    pecasJ2Y[i] += 0.01;

                    desenha();
                }
            }
            else if (pecasJ2X[i] < pecasJ2X_Destino && pecasJ2Y[i] > pecasJ2Y_Destino) // PEÇA IRÁ PARA DIREITA INFERIOR.
            {
                while (pecasJ2X[i] < pecasJ2X_Destino && pecasJ2Y[i] > pecasJ2Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    pecasJ2X[i] += 0.01;
                    pecasJ2Y[i] -= 0.01;

                    desenha();
                }
            }

            while (pecasJ2Z[i] > 1.625f) // DESCER A PEÇA.
            {
                pecasJ2Z[i] -= 0.025f;
                desenha();
            }

            moverCameraAnimacao = true;
            moverPecaAnimacao = false;

            if (pecasJ2Y_Destino == 4.5f) // 4.5f É A ÚLTIMA CASA DO TABULEIRO DE DAMA PARA O JOGADOR 2.
            {
                damasJ2[i] = 1; // TRANSFORMANDO A PEÇA EM DAMA.
            }

            pecasJ2X[i] = pecasJ2X_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            pecasJ2Y[i] = pecasJ2Y_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
        }
    }
}

void moverCamera()
{
    if (moverCameraAux == 1.0f)
    {
        while (eyeY != 66.0f)
        {
            eyeY += moverCameraAux;
            desenha();
        }
    }
    else
    {
        while (eyeY != -50.0f)
        {
            eyeY += moverCameraAux;
            desenha();
        }
    }

    moverCameraAux *= -1.0f;
    moverCameraAnimacao = false;

    jogadorDaVez *= -1;
    pecaSelecionada = false;
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

    if (moverPecaAnimacao)
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

    if (moverCameraAnimacao)
    {
        moverCamera();
    }
}
