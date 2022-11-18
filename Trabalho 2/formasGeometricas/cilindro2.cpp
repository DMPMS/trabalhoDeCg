#include "cilindro2.h"

#include <GL/gl.h>
#include <glm/glm.hpp>

void Cilindro::desenhaLinhas(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4ub(0, 0, 0, 0);

    float anguloDeCadaTriangulo = 2.0 * 3.14 / numLados;

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);

        for (int i = 0; i <= numLados; i++)
        {
            glVertex3f(cos(i * anguloDeCadaTriangulo) * raio,
                    sin(i * anguloDeCadaTriangulo) * raio,
                    0.0f);
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 1.0f);

        for (int i = 0; i <= numLados; i++)
        {
            glVertex3f(cos(i * anguloDeCadaTriangulo) * raio,
                    sin(i * anguloDeCadaTriangulo) * raio,
                    1.0f);
        }
    glEnd();

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


}

void Cilindro::desenhaGouraud(glm::vec3 cor, Luz &luz, int texId){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(cor.r, cor.g, cor.b);

    glm::vec3 P, C;

    float anguloDeCadaTriangulo = 2.0 * 3.14 / numLados;

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_TRIANGLES);
        for (int i = 0; i <= numLados; i++)
        {
            //BASE
            P = glm::vec3(0.0f, 0.0f, 0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                          sin(i * anguloDeCadaTriangulo) * raio,
                          0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);   glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos((i+1) * anguloDeCadaTriangulo) * raio,
                          sin((i+1) * anguloDeCadaTriangulo) * raio,
                          0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);

            // TOPO
            P = glm::vec3(0.0f, 0.0f, 1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                          sin(i * anguloDeCadaTriangulo) * raio,
                          1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos((i+1) * anguloDeCadaTriangulo) * raio,
                          sin((i+1) * anguloDeCadaTriangulo) * raio,
                          1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);

            // LATERAL 1
            P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                          sin(i * anguloDeCadaTriangulo) * raio,
                          0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos((i+1) * anguloDeCadaTriangulo) * raio,
                          sin((i+1) * anguloDeCadaTriangulo) * raio,
                          0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos((i+1) * anguloDeCadaTriangulo) * raio,
                          sin((i+1) * anguloDeCadaTriangulo) * raio,
                          1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            // LATERAL 2

            P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                          sin(i * anguloDeCadaTriangulo) * raio,
                          1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos((i+1) * anguloDeCadaTriangulo) * raio,
                          sin((i+1) * anguloDeCadaTriangulo) * raio,
                          1.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);


            P = glm::vec3(cos(i * anguloDeCadaTriangulo) * raio,
                          sin(i * anguloDeCadaTriangulo) * raio,
                          0.0f);
            C = luz.ilumina(P, glm::normalize(P), cor);
            glColor3ub(C.r, C.g, C.b);
            glTexCoord2f(P.x, P.y);    glVertex3f(P.x, P.y, P.z);

        }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

}

Cilindro::Cilindro(float r, float g, float b){
    this->raio = 1;
    this->numLados = 361;
    cor            = glm::vec3(r, g, b);
    mostraLinhas   = false;
}

void Cilindro::setCor(float r, float g, float b){
    cor = glm::vec3(r,g,b);
}

void Cilindro::mostraLinhasOnOff(){
    mostraLinhas = !mostraLinhas; //alterna entre ligado e desligado as linhas divisórias da grade
}

void Cilindro::desenha(Luz &luz, int texId){
    desenhaGouraud(cor, luz, texId);
    if(mostraLinhas) desenhaLinhas();
}
