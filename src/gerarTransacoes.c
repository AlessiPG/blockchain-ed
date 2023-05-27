// codigo provisorio para testes

#include <stdlib.h>
#include <string.h>
#include "projeto.h"
#include "mtwister.h"
void gerarTransacoes(unsigned char *data)
{
    if (!data)
        return NULL;
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[183] = 2;
}