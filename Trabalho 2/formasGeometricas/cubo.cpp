#include "cubo.h"

#include <glm/glm.hpp>
#include <GL/gl.h>

extern glm::vec3 eye;

void Cubo::desenhaGouraud(glm::vec3 cor, Luz &luz, int texId)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(cor.r, cor.g, cor.b);

    float A1[] = {0.5f, 0.5f, 0.0f};
    float A2[] = {0.5f, -0.5f, 0.0f};
    float A3[] = {-0.5f, -0.5f, 0.0f};
    float A4[] = {-0.5f, 0.5f, 0.0f};

    glm::vec3 P, C;

    // luz.ilumina(posicao da luz, normal da superficie, cor)
    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS); // BASE
    P = glm::vec3(A1[0], A1[1], A1[2]);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A2[0], A2[1], A2[2]);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A3[0], A3[1], A3[2]);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A4[0], A4[1], A4[2]);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS); // TOPO
    P = glm::vec3(A1[0], A1[1], A1[2] + 1.0);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A2[0], A2[1], A2[2] + 1.0);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A3[0], A3[1], A3[2] + 1.0);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(A4[0], A4[1], A4[2] + 1.0);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    float *vertices[] = {A1, A2, A3, A4};

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUAD_STRIP); // FACES LATERAIS

    for (int i = 0; i < 4; i++)
    {
        P = glm::vec3(vertices[i][0], vertices[i][1], vertices[i][2]);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(vertices[i][0], vertices[i][1], vertices[i][2] + 1.0);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);
    }
    P = glm::vec3(vertices[0][0], vertices[0][1], vertices[0][2]);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    P = glm::vec3(vertices[0][0], vertices[0][1], vertices[0][2] + 1.0);
    C = luz.ilumina(P, glm::normalize(P), cor, eye);
    glColor3ub(C.r, C.g, C.b);
    glTexCoord2f(P.x, P.y);
    glVertex3f(P.x, P.y, P.z);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

Cubo::Cubo(int r, int g, int b)
{
    cor = glm::vec3(r, g, b);
}

void Cubo::setCor(int r, int g, int b)
{
    cor = glm::vec3(r, g, b);
}

void Cubo::desenha(Luz &luz, int texId)
{
    desenhaGouraud(cor, luz, texId);
}
