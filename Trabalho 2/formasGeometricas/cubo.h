#ifndef CUBO
#define CUBO

#include <math.h>

void cubo(int corR, int corG, int corB, int corO, int modo)
{
    glPolygonMode(GL_FRONT_AND_BACK, modo);

    glColor4ub(corR, corG, corB, corO);

    float A1[] = {0.5f, 0.5f, 0.0f};
    float A2[] = {0.5f, -0.5f, 0.0f};
    float A3[] = {-0.5f, -0.5f, 0.0f};
    float A4[] = {-0.5f, 0.5f, 0.0f};

    glBegin(GL_QUADS); // BASE
    glVertex3f(A1[0], A1[1], A1[2]);
    glVertex3f(A2[0], A2[1], A2[2]);
    glVertex3f(A3[0], A3[1], A3[2]);
    glVertex3f(A4[0], A4[1], A4[2]);
    glEnd();

    glBegin(GL_QUADS); // TOPO
    glVertex3f(A1[0], A1[1], A1[2] + 1.0f);
    glVertex3f(A2[0], A2[1], A2[2] + 1.0f);
    glVertex3f(A3[0], A3[1], A3[2] + 1.0f);
    glVertex3f(A4[0], A4[1], A4[2] + 1.0f);
    glEnd();

    float *vertices[] = {A1, A2, A3, A4};

    glBegin(GL_QUAD_STRIP); // FACES LATERAIS

    for (int i = 0; i < 4; i++)
    {
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2] + 1.0f);
    }

    glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
    glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2] + 1.0f);

    glEnd();
}

#endif
