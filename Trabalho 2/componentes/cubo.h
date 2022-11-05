#ifndef CUBO
#define CUBO

#include <glm/vec3.hpp>

class Cubo
{
private:
    glm::vec3 vertices[4];
    glm::vec3 cor;
    void modoDesenho(int modo, glm::vec3 cor);
public:
    Cubo(glm::vec3 cor = glm::vec3(1.0f));
    void setCor(glm::vec3 cor);
    void desenha();
};

#endif
