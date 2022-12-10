#ifndef cubo
#define cubo

#include <math.h>
#include <glm/vec3.hpp>
#include "../iluminacao/luz.h"

class Cubo
{
private:
    glm::vec3 cor;
    void desenhaGouraud(glm::vec3 cor, Luz &luz, int textId);

public:
    Cubo(int r = 0, int g = 255, int b = 255);
    void setCor(int r, int g, int b);
    void desenha(Luz &luz, int texId);
};

#endif