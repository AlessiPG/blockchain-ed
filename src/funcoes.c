#include <stdio.h>
#include <string.h>
#include "projeto.h"

// endereço com mais bitcoins e o número de bitcoins dele (liste mais de um em caso de empate)
void maisBitcoins(Blockchain *blc) {
    unsigned int maiorN = 0;
    No *maiores = gerarNo(0); // lista para guardar os endereços com mais bitcoins
    int index = 0;

    for (int i = 0; i < CARTEIRA_TAM; i++) {
        if (blc->clientes.carteira[i] > maiorN) {
            maiorN = blc->clientes.carteira[i];
            freeEmLista(maiores);
            maiores = gerarNo(i);
        } else if (blc->clientes.carteira[i] == maiorN) {
            maiores = adicionaNo(maiores, i);
        }
    }
    
    printf("O(s) endereços ");
    printaNos(maiores);
    printf(" possuem %d, que é o maior número de bitcoins.\n", maiorN);
}
