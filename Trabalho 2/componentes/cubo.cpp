#include "cubo.h"

#include <GL/gl.h>

void Cubo::modoDesenho(int modo, glm::vec3 cor)
{
    glPolygonMode(GL_FRONT_AND_BACK, modo);

    glColor3ub(cor.r, cor.g, cor.b);

    // BASE
    glBegin(GL_QUADS);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
    glEnd();

    // TOPO
    glBegin(GL_QUADS);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z + 1.0f);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z + 1.0f);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z + 1.0f);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z + 1.0f);
    glEnd();

    // FACES LATERAIS
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z + 1.0f);
    }

    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z + 1.0f);
    glEnd();
}

Cubo::Cubo(glm::vec3 cor)
{
    this->cor = cor;
    vertices[0] = glm::vec3(0.5f, 0.5f, 0.0f);
    vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
    vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertices[3] = glm::vec3(-0.5f, 0.5f, 0.0f);
}

void Cubo::setCor(glm::vec3 cor)
{
    this->cor = cor;
}

void Cubo::desenha()
{
    modoDesenho(GL_FILL, cor);
    modoDesenho(GL_LINE, glm::vec3(0));
}
