// DAVI MONTEIRO PEDROSA MOREIRA SALES - 496314

#include <GL/glut.h>

#include "cenario/outros.h"
#include "cenario/baseDeMadeira.h"
#include "cenario/tabuleiro.h"
#include "cenario/damas.h"

#include "stdbool.h"

float eyeX = 15.0f;
float eyeY = -50.0f;
float eyeZ = 50.0f;

float seletorX = 0.0f;
float seletorY = 0.0f;

bool damaSelecionada = false;

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
        damaSelecionada += -1;
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

    eixos();

    glutSwapBuffers();
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
}
