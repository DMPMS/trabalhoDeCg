#include "luz.h"

#include <glm/glm.hpp>
#include <math.h>

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
glm::vec3 Luz::ilumina(glm::vec3 P, glm::vec3 normal, glm::vec3 color, glm::vec3 cameraEye)
{
    glm::vec3 Ia = this->ambiente;
    glm::vec3 Id = this->difusa;
    glm::vec3 Is = this->especular;

    // CÁLCULO DO VETOR NORMAL.
    glm::vec3 N = glm::normalize(normal);
    // CÁLCULO DO VETOR QUE APONTA NA DIREÇÃO DA FONTE DE LUZ.
    glm::vec3 L = glm::normalize(posicao - P);
    // CÁLCULO DO VETOR DE REFLEXAO EM RELAÇÃO A FONTE DE LUZ.
    glm::vec3 R = glm::normalize((glm::vec3(2) * glm::max(glm::dot(N, L), 0.0f), N) - L); // 2*(N * L)*N - L
    // CALCULO DO VETOR V.
    glm::vec3 V = glm::normalize(cameraEye - P);

    // CÁLCULO DAS REFLEXAO DO AMBIENTE, DIFUSO E ESPECULAR DE PHONG.
    glm::vec3 Ra = glm::vec3(0.1);                                              // Ra = Ia * Ka
    glm::vec3 Rd = glm::max(glm::dot(L, N), 0.0f) * color;                      // Rd = Id * Kd * (L * N)
    glm::vec3 Rs = glm::vec3(pow(glm::max(glm::dot(V, R), 0.0f), 100)) * color; // Rs = Is * Ks * (V * R)°

    // MULTIPLICANDO PROPRIEDADES DA FONTE DE LUZ.
    glm::vec3 ambiente =  Ia * Ra;
    glm::vec3 difusa =    Id * Rd;
    glm::vec3 especular = Is * Rs;

    // COR FINAL.
    glm::vec3 corFinal = ambiente + difusa + especular;

    return corFinal;
}
