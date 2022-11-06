// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/damas.h"

#include "stdbool.h"

float eyeX = 0.0f;
// float eyeX = 8.0f;
float eyeY = -50.0f;
float eyeZ = 70.0f;

// PARA MOVIMENTAÇÃO DO SELETOR DE DAMA.
float seletorX = 0.0f;
float seletorY = 0.0f;

float damasJ1X[12] = {5.5f, 7.5f, 9.5f, 11.5f,
                      4.5f, 6.5f, 8.5f, 10.5f,
                      5.5f, 7.5f, 9.5f, 11.5f};
float damasJ1Y[12] = {6.5f, 6.5f, 6.5f, 6.5f,
                      5.5f, 5.5f, 5.5f, 5.5f,
                      4.5f, 4.5f, 4.5f, 4.5f};
float damasJ1Z[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f};

float damasJ2X[12] = {10.5f, 8.5f, 6.5f, 4.5f,
                      11.5f, 9.5f, 7.5f, 5.5f,
                      10.5f, 8.5f, 6.5f, 4.5f};
float damasJ2Y[12] = {11.5f, 11.5f, 11.5f, 11.5f,
                      10.5f, 10.5f, 10.5f, 10.5f,
                      9.5f, 9.5f, 9.5f, 9.5f};
float damasJ2Z[12] = {1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f,
                      1.625f, 1.625f, 1.625f, 1.625f};

bool damaSelecionada = true;    // PARA EXIBIR (OU NÃO) AS OPÇÕES DE MOVIMENTO DA DAMA.
bool moverDamaAnimacao = false; // PARA INDICAR SE A ANIMAÇÃO DO MOVIMENTO DA DAMA FOI FINALIZADA.
char moverDamaLado;             // PARA DEFINIR SE A DAMA VAI PARA ESQUERDA OU DIREITA.

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

    // ESCOLHER PARA ONDE A DAMA VAI.
    switch (key)
    {
    case 'e':
    case 'E':
        // temDamaNaCasa(seletorX, seletorY) RETORNARÁ SE HÁ UMA DAMA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE DAMA.
        if (podeIrPraEsquerda(seletorX, seletorY) && damaSelecionada && temDamaNaCasa(seletorX, seletorY))
        {
            moverDamaLado = 'E';
            moverDamaAnimacao = true;
        }
        break;
    case 'd':
    case 'D':
        // temDamaNaCasa(seletorX, seletorY) RETORNARÁ SE HÁ UMA DAMA OU NÃO NA MESMA CASA ONDE ESTÁ O SELETOR DE DAMA.
        if (podeIrPraDireita(seletorX, seletorY) && damaSelecionada && temDamaNaCasa(seletorX, seletorY))
        {
            moverDamaLado = 'D';
            moverDamaAnimacao = true;
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
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 11.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA h.
        if (4.0f + seletorX < 11.0f)
        {
            seletorX += 1.0f;
            damaSelecionada = false;
        }
        break;
    case GLUT_KEY_LEFT:
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 4.0f REPRESENTA A COORDENADA x DO VÉRTICE A3 DE QUALQUER CASA DA COLUNA a.
        if (4.0f + seletorX > 4.0f)
        {
            seletorX -= 1.0f;
            damaSelecionada = false;
        }
        break;
    case GLUT_KEY_UP:
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 11.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 8.
        if (4.0f + seletorY < 11.0f)
        {
            seletorY += 1.0f;
            damaSelecionada = false;
        }
        break;
    case GLUT_KEY_DOWN:
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DO SELETOR DE DAMAS.
        // 4.0f REPRESENTA A COORDENADA y DO VÉRTICE A3 DE QUALQUER CASA DA LINHA 1.
        if (4.0f + seletorY > 4.0f)
        {
            seletorY -= 1.0f;
            damaSelecionada = false;
        }
        break;
    case GLUT_KEY_F1:
        damaSelecionada += -1; // HABILITA A EXIBIÇÃO DAS OPÇÕES DE MOVIMENTO DA DAMA SELECIONADA.
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

    damas();
    seletorDeDama(seletorX, seletorY, damaSelecionada);

    // eixos();

    glutSwapBuffers();
}

void moverDama()
{
    // PARA SELECIONAR A DAMA QUE ESTÁ NA MESMA CASA DO SELETOR DE DAMAS.
    for (int i = 0; i < 12; i++)
    {
        if (4.5f + seletorX == damasJ1X[i] && 4.5f + seletorY == damasJ1Y[i])
        {
            float damasJ1Y_Destino = damasJ1Y[i] + 1.0f;

            float damasJ1X_Destino;
            if (moverDamaLado == 'E') // VERIFICANDO SE A DAMA VAI PARA ESQUERDA OU DIREITA.
            {
                damasJ1X_Destino = damasJ1X[i] - 1.0f;
            }
            else if (moverDamaLado == 'D')
            {
                damasJ1X_Destino = damasJ1X[i] + 1.0f;
            }

            while (damasJ1Z[i] < 2.0f) // LEVANTAR A DAMA
            {
                damasJ1Z[i] += 0.025f;
                desenha();
            }

            // A AÇÃO DE INCREMENTAR/DECREMENTAR DEPENDERÁ SE A DAMA VAI PARA ESQUERDA OU DIREITA.
            if (damasJ1X[i] < damasJ1X_Destino)
            {
                while (damasJ1X[i] < damasJ1X_Destino && damasJ1Y[i] < damasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    damasJ1X[i] += 0.01;
                    damasJ1Y[i] += 0.01;

                    desenha();
                }
            }
            else if (damasJ1X[i] > damasJ1X_Destino)
            {
                while (damasJ1X[i] > damasJ1X_Destino && damasJ1Y[i] < damasJ1Y_Destino) // MOVER ATÉ A CASA SELECIONADA.
                {
                    damasJ1X[i] -= 0.01;
                    damasJ1Y[i] += 0.01;

                    desenha();
                }
            }

            while (damasJ1Z[i] > 1.625f) // DESCER A DAMA.
            {
                damasJ1Z[i] -= 0.025f;
                desenha();
            }

            moverCameraAnimacao = true;
            moverDamaAnimacao = false;
            damasJ1X[i] = damasJ1X_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
            damasJ1Y[i] = damasJ1Y_Destino; // ISSO NÃO É REDUNDANTE, É NECESSÁRIO PARA PODER MOVER A PEÇA.
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

    if (moverDamaAnimacao)
    {
        moverDama();
    }

    // if (moverCameraAnimacao)
    // {
    //     moverCamera();
    // }
}
