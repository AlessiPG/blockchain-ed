#include "projeto.h"

float acharMediaBitcoins(Blockchain bc, unsigned int carteira[])
{
    float media = 0;
    for (unsigned int i = 0; i < bc.tamanho; i++) {
        media += carteira[i];
    }

    media = media / bc.tamanho;

    return media;
}
