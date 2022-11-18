
#include "textura.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

#include "GL/gl.h"
#include <iostream>

using namespace std;

Textura::Textura()
{
    largura = altura = canais = id = 0;
}
unsigned int Textura::get_id()
{
    return id;
}

void Textura::carregar(string arquivo)
{

    stbi_set_flip_vertically_on_load(true);
    imagem = stbi_load(arquivo.c_str(), &largura, &altura, &canais, 0);

    if (!imagem)
    {
        cout << "Arquivo " << arquivo.c_str() << "Erro ao carregar imagem!" << endl;
    }
    else
    {
        cout << "Arquivo " << arquivo.c_str() << " carregado com sucesso!" << endl;
    }

    // criar textura
    glGenTextures(1, &id);            // criacao
    glBindTexture(GL_TEXTURE_2D, id); // definindo o tipo e o id da textura

    // propriedades
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE); // GL_COMPILE.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, imagem);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imagem);
}
