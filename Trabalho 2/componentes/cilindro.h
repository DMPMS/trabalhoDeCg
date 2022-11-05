#ifndef CILINDRO
#define CILINDRO

#include <glm/vec3.hpp>

class Cilindro
{
private:
    glm::vec3 cor;
    void modoDesenho(int modo, glm::vec3 cor);

public:
    Cilindro(glm::vec3 cor = glm::vec3(1.0f));
    void setCor(glm::vec3 cor);
    void desenha();
};

#endif
