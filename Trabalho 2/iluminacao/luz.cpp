#include "luz.h"

#include <glm/glm.hpp>

Luz::Luz(glm::vec3 posicao)
{
    this->posicao = posicao;
    ambiente = glm::vec3(0.1);
    difusa = glm::vec3(1.0);
    especular = glm::vec3(1.0);
}

glm::vec3 Luz::getPosicao()
{
    return posicao;
}

void Luz::setPosicao(glm::vec3 posicao)
{
    this->posicao = posicao;
}

void Luz::setAmbiente(glm::vec3 ambiente)
{
    this->ambiente = glm::clamp(ambiente, glm::vec3(0), glm::vec3(1));
}

void Luz::setDifusa(glm::vec3 difusa)
{
    this->difusa = glm::clamp(difusa, glm::vec3(0), glm::vec3(1));
}

void Luz::setEspecular(glm::vec3 especular)
{
    this->especular = glm::clamp(especular, glm::vec3(0), glm::vec3(1));
}

// IMPLEMENTAÇÃO ILUMINAÇÃO DE PHONG.
glm::vec3 Luz::ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color)
{
    glm::vec3 Ia = this->ambiente;
    glm::vec3 Id = this->difusa;
    glm::vec3 Is = this->especular;

    // CÁLCULO DOS VETORES NORMAIS E VETOR QUE APONTA NA DIREÇÃO DA FONTE DE LUZ.
    glm::vec3 N = glm::normalize(normal);
    glm::vec3 L = glm::normalize(posicao - pos);

    // CÁLCULO DOS COMPONENTES AMBIENTE, DIFUSO E ESPECULAR DE PHONG (SEM ESPECULAR).
    glm::vec3 Ra = glm::vec3(0.1);
    glm::vec3 Rd = glm::max(glm::dot(L, N), 0.0f) * color; // color: PROPRIEDADE DIFUSA DO MATERIAL.
    glm::vec3 Rs = glm::max(glm::dot(L, N), 0.0f) * color; // color: PROPRIEDADE DIFUSA DO MATERIAL.

    // MULTIPLICANDO PROPRIEDADES DA FONTE DE LUZ.
    glm::vec3 ambiente = Ia * Ra;
    glm::vec3 difusa = Id * Rd;

    // COR FINAL (SEM ESPECULAR).
    glm::vec3 corFinal = ambiente + difusa;

    return corFinal;
}
