#ifndef TEXTURA_H
#define TEXTURA_H
#include <iostream>

using namespace std;

class Textura
{
private:
    int largura, altura, canais;
    unsigned char *imagem;
    unsigned int id;

public:
    Textura();
    void carregar(string arquivo);
    unsigned int get_id();
};

#endif // TEXTURA_H
