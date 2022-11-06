#ifndef CILINDRO
#define CILINDRO

#include <math.h>

void circulo(float raio, float altura, float numLados)
{
    float anguloDeCadaTriangulo = 2.0 * 3.14 / numLados;

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, 0.0f, altura);

    for (int i = 0; i <= numLados; i++)
    {
        glVertex3f(cos(i * anguloDeCadaTriangulo) * raio,
                   sin(i * anguloDeCadaTriangulo) * raio,
                   altura);
    }

    glEnd();
}

void cilindro(int corR, int corG, int corB, int corO, int modo)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float anguloDeCadaTriangulo = 2.0 * 3.14 / 360;

    glColor4ub(corR, corG, corB, corO);

    glBegin(GL_QUAD_STRIP); // LATERAIS

    for (int i = 0; i <= 360; i++)
    {
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   0.0f);
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   1.0f);
    }

    glEnd();

    circulo(1.0f, 1.0f, 360); // TOPO

    circulo(1.0f, 0.0f, 360); // BASE
}

#endif
