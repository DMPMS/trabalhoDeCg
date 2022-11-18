#ifndef CILINDRO2
#define CILINDRO2

#include <math.h>
#include <glm/vec3.hpp>
#include "../iluminacao/luz.h"

class Cilindro{
    private:
        glm::vec3 cor;          //cor
        float raio = 1;
        float numLados = 361;
        bool mostraLinhas;      //exibe ou não as linhas das divisórias da grade
        void desenhaLinhas();
        void desenhaGouraud(glm::vec3 cor, Luz &luz, int texId); //desenha o cubo com Gouraud Shading
    public:
        Cilindro(float r = 0, float g = 255, float b = 255);
        void  setCor(float r, float g, float b);
        void  mostraLinhasOnOff();
        void  desenha(Luz &luz, int texId);
};

#endif