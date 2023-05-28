#include "projeto.h"
//#include <stdio.h>
//#include <stdlib.h>

int main(void) {
    Blockchain *corrente = inicializaBlockchain();
    if (!corrente) return -1;
    
    for (int i = 0; i < TOTAL_BLOCOS; i++) {
        novoBloco(corrente);
    }

    return 0;
}
