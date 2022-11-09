// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/pecasJ1.h"

#include "stdbool.h"

float eyeX = 0.0f;
// float eyeX = 8.0f;
float eyeY = -50.0f;
float eyeZ = 70.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE PEÇA.
float seletorJ1X = 0.0f;
float seletorJ1Y = 0.0f;

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
char moverPecaLado;             // PARA DEFINIR SE A PEÇA VAI PARA ESQUERDA OU DIREITA.

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
        // temPecaNaCasa(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
        if (ehUmaDama(seletorJ1X, seletorJ1Y) && podeIrPraBaixo(seletorJ1X, seletorJ1Y) && podeIrPraEsquerdaInferior(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasa(seletorJ1X, seletorJ1Y))
        {
            moverPecaLado = 'e';
            moverPecaAnimacao = true;
        }
        break;
    case 'E':
        // temPecaNaCasa(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
        if (podeIrPraCima(seletorJ1X, seletorJ1Y) && podeIrPraEsquerdaSuperior(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasa(seletorJ1X, seletorJ1Y))
        {
            moverPecaLado = 'E';
            moverPecaAnimacao = true;
        }
        break;
    case 'd':
        // temPecaNaCasa(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
        if (ehUmaDama(seletorJ1X, seletorJ1Y) && podeIrPraBaixo(seletorJ1X, seletorJ1Y) && podeIrPraDireitaInferior(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasa(seletorJ1X, seletorJ1Y))
        {
            moverPecaLado = 'd';
            moverPecaAnimacao = true;
        }
        break;
    case 'D':
        // temPecaNaCasa(seletorJ1X, seletorJ1Y) RETORNARÁ SE HÁ UMA PEÇA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE PEÇA.
        if (podeIrPraCima(seletorJ1X, seletorJ1Y) && podeIrPraDireitaSuperior(seletorJ1X, seletorJ1Y) && pecaSelecionada && temPecaNaCasa(seletorJ1X, seletorJ1Y))
        {
            moverPecaLado = 'D';
            moverPecaAnimacao = true;
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
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
        // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h (CONSULTAR NOTAÇÃO ALGÉBRICA).
        if (4.0f + seletorJ1X < 11.0f)
        {
            seletorJ1X += 1.0f;
            pecaSelecionada = false;
        }
        break;
    case GLUT_KEY_LEFT:
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE PEÇAS.
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a (CONSULTAR NOTAÇÃO ALGÉBRICA).
        if (4.0f + seletorJ1X > 4.0f)
        {
            seletorJ1X -= 1.0f;
            pecaSelecionada = false;
        }
        break;
    case GLUT_KEY_UP:
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
        // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8 (CONSULTAR NOTAÇÃO ALGÉBRICA).
        if (4.0f + seletorJ1Y < 11.0f)
        {
            seletorJ1Y += 1.0f;
            pecaSelecionada = false;
        }
        break;
    case GLUT_KEY_DOWN:
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE PEÇAS.
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1 (CONSULTAR NOTAÇÃO ALGÉBRICA).
        if (4.0f + seletorJ1Y > 4.0f)
        {
            seletorJ1Y -= 1.0f;
            pecaSelecionada = false;
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

    pecas();
    seletorDePeca(seletorJ1X, seletorJ1Y, pecaSelecionada);

    // eixos();

    glutSwapBuffers();
}

void moverPeca()
{
    // PARA SELECIONAR A PEÇA QUE ESTÁ NA MESMA CASA DO SELETOR DE PEÇAS.
    for (int i = 0; i < 12; i++)
    {
        if (4.5f + seletorJ1X == pecasJ1X[i] && 4.5f + seletorJ1Y == pecasJ1Y[i])
        {
            float pecasJ1Y_Destino;
            float pecasJ1X_Destino;

            if (moverPecaLado == 'E') // SE A PEÇA VAI PRA ESQUERDA SUPERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] - 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] + 1.0f;
            }
            else if (moverPecaLado == 'e') // SE A PEÇA VAI PRA ESQUERDA INFERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] - 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] - 1.0f;
            }
            else if (moverPecaLado == 'D') // SE A PEÇA VAI PRA DIREITA SUPERIOR.
            {
                pecasJ1X_Destino = pecasJ1X[i] + 1.0f;
                pecasJ1Y_Destino = pecasJ1Y[i] + 1.0f;
            }
            else if (moverPecaLado == 'd') // SE A PEÇA VAI PRA DIREITA INFERIOR.
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
        moverPeca();
    }

    // if (moverCameraAnimacao)
    // {
    //     moverCamera();
    // }
}
