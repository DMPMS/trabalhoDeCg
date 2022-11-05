#include "Cilindro.h"

#include <GL/gl.h>
#include <math.h>

void Cilindro::modoDesenho(int modo, glm::vec3 cor)
{
    glPolygonMode(GL_FRONT_AND_BACK, modo);
    glColor3ub(cor.r, cor.g, cor.b);

    float anguloDeCadaTriangulo = 2.0 * 3.14 / 360;

    // BASE
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 360; i++)
    {
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   0.0f);
    }
    glEnd();

    // TOPO
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 360; i++)
    {
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   1.0f);
    }
    glEnd();

    // LATERAIS
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 360; i++)
    {
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   0.0f);
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   1.0f);
    }
    glEnd();
}

Cilindro::Cilindro(glm::vec3 cor)
{
    this->cor = cor;
}

void Cilindro::setCor(glm::vec3 cor)
{
    this->cor = cor;
}

void Cilindro::desenha()
{
    modoDesenho(GL_FILL, cor);
    // modoDesenho(GL_LINE, glm::vec3(0));
}
