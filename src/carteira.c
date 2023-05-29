#include <stdlib.h>
#include "projeto.h"

unsigned int * copiaCarteira(unsigned int car[]) {
    unsigned int *nova = malloc(sizeof(unsigned int) * CARTEIRA_TAM);

    for (int i = 0; i < CARTEIRA_TAM; i++) {
        nova[i] = car[i];
    }

    return nova;
}
