#include "cilindro.h"

#include <GL/gl.h>
#include <glm/glm.hpp>

extern glm::vec3 eye;

void Cilindro::desenhaGouraud(glm::vec3 cor, Luz &luz, int texId)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(cor.r, cor.g, cor.b);

    glm::vec3 P, C;

    float anguloDeCadaTriangulo = 2.0 * 3.14 / numLados;

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i <= numLados; i++)
    {
        // BASE
        P = glm::vec3(0.0f, 0.0f, 0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                      sin(i * anguloDeCadaTriangulo) * raio,
                      0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos((i + 1) * anguloDeCadaTriangulo) * raio,
                      sin((i + 1) * anguloDeCadaTriangulo) * raio,
                      0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        // TOPO
        P = glm::vec3(0.0f, 0.0f, 1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                      sin(i * anguloDeCadaTriangulo) * raio,
                      1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos((i + 1) * anguloDeCadaTriangulo) * raio,
                      sin((i + 1) * anguloDeCadaTriangulo) * raio,
                      1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        // LATERAL 1
        P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                      sin(i * anguloDeCadaTriangulo) * raio,
                      0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos((i + 1) * anguloDeCadaTriangulo) * raio,
                      sin((i + 1) * anguloDeCadaTriangulo) * raio,
                      0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos((i + 1) * anguloDeCadaTriangulo) * raio,
                      sin((i + 1) * anguloDeCadaTriangulo) * raio,
                      1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        // LATERAL 2

        P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                      sin(i * anguloDeCadaTriangulo) * raio,
                      1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos((i + 1) * anguloDeCadaTriangulo) * raio,
                      sin((i + 1) * anguloDeCadaTriangulo) * raio,
                      1.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);

        P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                      sin(i * anguloDeCadaTriangulo) * raio,
                      0.0f);
        C = luz.ilumina(P, glm::normalize(P), cor, eye);
        glColor3ub(C.r, C.g, C.b);
        glTexCoord2f(P.x, P.y);
        glVertex3f(P.x, P.y, P.z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

Cilindro::Cilindro(int r, int g, int b)
{
    this->raio = 1;
    this->numLados = 10;
    cor = glm::vec3(r, g, b);
}

void Cilindro::setCor(int r, int g, int b)
{
    cor = glm::vec3(r, g, b);
}

void Cilindro::desenha(Luz &luz, int texId)
{
    desenhaGouraud(cor, luz, texId);
}
