#include "projeto.h"
//#include <stdio.h>
//#include <stdlib.h>

int main(void) {
    Blockchain *corrente = inicializaBlockchain();
    if (!corrente) return -1;

    novoBloco(corrente);

    return 0;
}
