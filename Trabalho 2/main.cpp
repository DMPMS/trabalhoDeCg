#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "stdbool.h"

#include "componentes/outros.h"

glm::vec3 camEye(20.0f, -20.0f, 10.0f);

float auxXselecaoPeca = 0.0f;
float auxYselecaoPeca = 0.0f;

bool mostrarOpcoesDaPeca_aux = false;

void inicio()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1);
    glEnable(GLUT_MULTISAMPLE);
}

void tecladoASCII(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '7':
        camEye.x += 3.0f;
        break;
    case '1':
        camEye.x -= 3.0f;
        break;
    case '8':
        camEye.y += 3.0f;
        break;
    case '2':
        camEye.y -= 3.0f;
        break;
    case '9':
        camEye.z += 3.0f;
        break;
    case '3':
        camEye.z -= 3.0f;
        break;
    }

    glutPostRedisplay();
}

void tecladoSpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        // 4.0f REPRESENTA A COORDENADA x INICIAL DE UM DETERMINADO VÉRTICE DO PARALELEPÍPELO QUE SELECIONA AS PEÇAS.
        // 11.0f REPRESENTA A COORDENADA x DO LIMITE DO LADO DIREITO DO TABULEIRO.
        if (4.0f + auxXselecaoPeca < 11.0f)
        {
            auxXselecaoPeca += 1.0f;
        }
        break;
    case GLUT_KEY_LEFT:
        // 4.0f REPRESENTA A COORDENADA x INICIAL DE UM DETERMINADO VÉRTICE DO PARALELEPÍPELO QUE SELECIONA AS PEÇAS.
        // 4.0f REPRESENTA A COORDENADA x DO LIMITE DO LADO ESQUERDO DO TABULEIRO.
        if (4.0f + auxXselecaoPeca > 4.0f)
        {
            auxXselecaoPeca -= 1.0f;
        }
        break;
    case GLUT_KEY_UP:
        // 4.0f REPRESENTA A COORDENADA y INICIAL DE UM DETERMINADO VÉRTICE DO PARALELEPÍPELO QUE SELECIONA AS PEÇAS.
        // 11.0f REPRESENTA A COORDENADA y DO LIMITE DO TOPO DO TABULEIRO.
        if (4.0f + auxYselecaoPeca < 11.0f)
        {
            auxYselecaoPeca += 1.0f;
        }
        break;
    case GLUT_KEY_DOWN:
        // 4.0f REPRESENTA A COORDENADA y INICIAL DE UM DETERMINADO VÉRTICE DO PARALELEPÍPELO QUE SELECIONA AS PEÇAS.
        // 11.0f REPRESENTA A COORDENADA y DO LIMITE DA BASE DO TABULEIRO.
        if (4.0f + auxYselecaoPeca > 4.0f)
        {
            auxYselecaoPeca -= 1.0f;
        }
        break;
    case GLUT_KEY_F1:
        mostrarOpcoesDaPeca_aux += -1;
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
    glm::mat4 matrizCamera = glm::lookAt(camEye,
                                         glm::vec3(8.0f, 8.0f, 0.0f),
                                         glm::vec3(0.0f, 0.0f, 1.0f));
    glMultMatrixf(glm::value_ptr(matrizCamera));
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projecao();
    camera();

    baseDeMadeira();
    baseTabuleiro();
    quadradoTabuleiro();

    damasJogador1();

    mostrarOpcoesDaPeca(mostrarOpcoesDaPeca_aux, auxXselecaoPeca, auxYselecaoPeca);
    moverSelecaoPeca(auxXselecaoPeca, auxYselecaoPeca);

    eixos();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(110, 50);
    glutInitWindowSize(720, 720);
    glutCreateWindow("Dama");

    inicio();

    glutDisplayFunc(desenha);
    glutKeyboardFunc(tecladoASCII);
    glutSpecialFunc(tecladoSpecial);

    glutMainLoop();

    return 0;
}
