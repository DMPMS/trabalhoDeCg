#ifndef LUZ_H
#define LUZ_H

#include <glm/vec3.hpp>

class Luz
{
private:
    glm::vec3 posicao;                     // FONTE DE LUZ PONTUAL
    glm::vec3 ambiente, difusa, especular; // PROPRIEDADES DA FONTE DE LUZ
public:
    Luz(glm::vec3 posicao = glm::vec3(0.0));
    glm::vec3 getPosicao();

    void setPosicao(glm::vec3 posicao);
    void setAmbiente(glm::vec3 ambiente);
    void setDifusa(glm::vec3 difusa);
    void setEspecular(glm::vec3 especular);

    glm::vec3 ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color);
};

#endif
