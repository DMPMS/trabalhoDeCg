#ifndef CILINDRO
#define CILINDRO

#include <math.h>
#include <glm/vec3.hpp>
#include "../iluminacao/luz.h"

class Cilindro
{
private:
    glm::vec3 cor;
    float raio = 1;
    int numLados = 10;
    void desenhaGouraud(glm::vec3 cor, Luz &luz, int texId);

public:
    Cilindro(int r = 0, int g = 255, int b = 255);
    void setCor(int r, int g, int b);
    void desenha(Luz &luz, int texId);
};

#endif