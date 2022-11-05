#ifndef OUTROS
#define OUTROS

#include "cubo.cpp"
#include "cilindro.cpp"
#include "stdbool.h"

Cubo baseDeMadeira_obj(glm::vec3(150, 75, 0));
Cubo baseTabuleiro_obj(glm::vec3(30, 30, 30));
Cubo quadradoTabuleiro_obj(glm::vec3(255, 30, 30));

Cilindro dama1Jogador1_obj(glm::vec3(0, 255, 255));

Cubo selecaoPeca(glm::vec3(40, 0, 0));

Cubo selecaoPecaEsq(glm::vec3(140, 0, 0));
Cubo selecaoPecaDir(glm::vec3(140, 0, 0));

void eixos()
{
    // EIXO x
    glBegin(GL_LINES);

    glColor3ub(255, 0, 255);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3ub(255, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glEnd();

    // EIXO y
    glBegin(GL_LINES);

    glColor3ub(255, 255, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);

    glColor3ub(0, 255, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glEnd();

    // EIXO z
    glBegin(GL_LINES);

    glColor3ub(0, 255, 255);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);

    glColor3ub(0, 0, 255);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
}

void baseDeMadeira()
{
    glPushMatrix();

    glScalef(16.0f, 16.0f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    baseDeMadeira_obj.desenha();

    glPopMatrix();
}

void baseTabuleiro()
{
    glPushMatrix();

    glTranslatef(3.0f, 3.0f, 1.0f);
    glScalef(10.0f, 10.0f, 0.5f);
    glTranslatef(0.5f, 0.5f, 0.0f);
    baseTabuleiro_obj.desenha();

    glPopMatrix();
}

void quadradoTabuleiro()
{

    float x[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
    float y[8] = {4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};

    int corR[2] = {99, 231};
    int corG[2]{53, 209};
    int corB[2] = {28, 133};

    bool aux = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            glPushMatrix();

            glTranslatef(x[i], y[j], 1.5f);
            glScalef(1.0f, 1.0f, 0.125f);
            glTranslatef(0.5f, 0.5f, 0.0f);
            quadradoTabuleiro_obj.setCor(glm::vec3(corR[aux], corG[aux], corB[aux]));
            quadradoTabuleiro_obj.desenha();

            glPopMatrix();

            aux += -1;
        }
        aux += -1;
    }
}

void moverSelecaoPeca(float auxXselecaoPeca, float auxYselecaoPeca)
{
    glPushMatrix();

    glTranslatef(4.5f + auxXselecaoPeca, 4.5f + auxYselecaoPeca, 1.625f);
    glScalef(1.0f, 1.0f, 0.125f);
    selecaoPeca.desenha();

    glPopMatrix();
}

void damasJogador1()
{
    glPushMatrix();

    glTranslatef(5.5f, 4.5f, 1.625f);
    glScalef(0.4f, 0.4f, 0.125f);
    dama1Jogador1_obj.desenha();

    glPopMatrix();
}

void mostrarOpcoesDaPeca(bool mostrarOpcoesDaPeca_aux, float auxXselecaoPeca, float auxYselecaoPeca)
{
    if (mostrarOpcoesDaPeca_aux)
    {
        // ESQUERDA
        glPushMatrix();

        glTranslatef(3.5f + auxXselecaoPeca, 5.5f + auxYselecaoPeca, 1.625f);
        glScalef(1.0f, 1.0f, 0.125f);
        selecaoPecaEsq.desenha();

        glPopMatrix();

        // DIREITA
        glPushMatrix();

        glTranslatef(5.5f + auxXselecaoPeca, 5.5f + auxYselecaoPeca, 1.625f);
        glScalef(1.0f, 1.0f, 0.125f);
        selecaoPecaDir.desenha();

        glPopMatrix();
    }
}
#endif
