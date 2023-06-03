#include "projeto.h"

void copiaCarteira(unsigned int orig[], unsigned int dest[])
{
    for (int i = 0; i < CARTEIRA_TAM; i++)
        dest[i] = orig[i];
}
