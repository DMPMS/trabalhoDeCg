#ifndef CILINDRO
#define CILINDRO

#include <math.h>


void circulo(float raio, float altura, float numLados, int texId)
{
    float anguloDeCadaTriangulo = 2.0 * 3.14 / numLados;

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.1, 0.1);
    glVertex3f(0.0f, 0.0f, altura);

    for (int i = 0; i <= numLados; i++)
    {
        float x = cos(i * anguloDeCadaTriangulo) * raio;
        float y = sin(i * anguloDeCadaTriangulo) * raio;

        glTexCoord2f(x, y);
        glVertex3f(cos(i * anguloDeCadaTriangulo) * raio,
                   sin(i * anguloDeCadaTriangulo) * raio,
                   altura);
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

}

void cilindro(int corR, int corG, int corB, int corO, int modo, int texId)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float anguloDeCadaTriangulo = 2.0 * 3.14 / 360;

    glColor4ub(corR, corG, corB, corO);

    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUAD_STRIP); // LATERAIS

    for (int i = 0; i <= 360; i++)
    {
        float x = cos(i * anguloDeCadaTriangulo) * 1.0f;
        float y = sin(i * anguloDeCadaTriangulo) * 1.0f;
        
        glTexCoord2f(x, y);
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   0.0f);
        glTexCoord2f(x, y);
        glVertex3f(cos(i * anguloDeCadaTriangulo) * 1.0f,
                   sin(i * anguloDeCadaTriangulo) * 1.0f,
                   1.0f);
    }

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    circulo(1.0f, 1.0f, 360, texId); // TOPO

    circulo(1.0f, 0.0f, 360, texId); // BASE
}

#endif
