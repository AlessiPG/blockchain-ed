#include "projeto.h"

int main(void) {
    Blockchain *corrente = inicializaBlockchain();
    if (!corrente) return -1;
    
    // subtraimos 1 de TOTAL_BLOCOS para levar o genesis em conta
    for (int i = 0; i < TOTAL_BLOCOS - 1; i++) {
        novoBloco(corrente);
    }
    
    menu(corrente);

    return 0;
}
