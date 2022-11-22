#ifndef cubo
#define cubo

#include <math.h>
#include <glm/vec3.hpp>
#include "../iluminacao/luz.h"

class Cubo{
    private:
        glm::vec3 cor;          //cor
        bool mostraLinhas;      //exibe ou não as linhas das divisórias da grade
        void desenhaLinhas();
        void desenhaGouraud(glm::vec3 cor, Luz &luz, int textId); //desenha o cubo com Gouraud Shading
    public:
        Cubo(float r = 0, float g = 255, float b = 255);
        void  setCor(float r, float g, float b);
        void  mostraLinhasOnOff();
        void  desenha(Luz &luz, int texId);
};

#endif