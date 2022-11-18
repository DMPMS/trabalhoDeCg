#include "luz.h"

#include <glm/glm.hpp>

Luz::Luz(glm::vec3 posicao){
    this->posicao = posicao;
    ambiente  = glm::vec3(0.1); //valor baixo pra propriedade ambiente (senão a cena fica com pouco contraste)
    difusa    = glm::vec3(1.0); //luz com propriedades difusa e especulares branca
    especular = glm::vec3(1.0);
}

glm::vec3 Luz::getPosicao(){
    return posicao;
}

void Luz::setPosicao(glm::vec3 posicao){
    this->posicao = posicao;
}

void Luz::setAmbiente(glm::vec3 ambiente){
    this->ambiente = glm::clamp(ambiente, glm::vec3(0), glm::vec3(1));
}

void Luz::setDifusa(glm::vec3 difusa){
    this->difusa = glm::clamp(difusa, glm::vec3(0), glm::vec3(1));
}

void Luz::setEspecular(glm::vec3 especular){
    this->especular = glm::clamp(especular, glm::vec3(0), glm::vec3(1));
}

//Função que implementa o modelo de iluminação de Phong (parcialmente neste caso)
glm::vec3 Luz::ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color){
    glm::vec3 Ia = this->ambiente;
    glm::vec3 Id = this->difusa;

    //calculando os vetores normal e vetor que aponta na direção da fonte de luz
    glm::vec3 N = glm::normalize(normal);
    glm::vec3 L = glm::normalize(posicao - pos);

    //calculando os componentes ambiente, difuso e especular de Phong (especular ausente)
    glm::vec3 Ra = glm::vec3(0.1);
    glm::vec3 Rd = glm::max(glm::dot(L,N),0.0f) * color; //usando 'color' como propriedade difusa do material

    //cada resultado deve ser multiplicado com as propriedades da fonte de luz correspondente
    glm::vec3 ambiente = Ia * Ra;
    glm::vec3 difusa   = Id * Rd;

    //cor final é a soma de todas as componentes (especular está ausente)
    glm::vec3 corFinal = ambiente + difusa;

    return corFinal;
}
